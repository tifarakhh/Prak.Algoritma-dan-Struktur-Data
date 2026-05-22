
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;



const int MAX_PASIEN  = 500;
const int MAX_DOKTER  = 50;
const int MAX_AKUN    = 30;
const int MAX_LOGIN   = 5;   // maks percobaan login

const string FILE_PASIEN = "pasien.txt";
const string FILE_REKAM  = "rekam_medis.txt";
const string FILE_DOKTER = "dokter.txt";
const string FILE_AKUN   = "akun.txt";

struct Akun {
    string username;
    string password;
    string role;     // admin atau petugas
};

Akun daftarAkun[MAX_AKUN];
int  jumlahAkun = 0;
Akun* akunAktif = nullptr;

//struct data

struct Dokter {
    string id;
    string nama;
    string spesialisasi;
};

struct NodeRekamMedis {
    string noRekam;
    string tanggal;
    string keluhan;
    string diagnosa;
    string obat;
    string idDokter;
    NodeRekamMedis* prev;
    NodeRekamMedis* next;

    NodeRekamMedis(string nr, string tgl, string kel, string dia,
                   string ob, string doc)
        : noRekam(nr), tanggal(tgl), keluhan(kel), diagnosa(dia),
          obat(ob), idDokter(doc), prev(nullptr), next(nullptr) {}
};

struct Pasien {
    string noPasien;
    string nama;
    string jenisKelamin;
    string tanggalLahir;
    string alamat;
    string noTelp;
    Dokter* dokterPenangani;
    NodeRekamMedis* headRekam;
    NodeRekamMedis* tailRekam;
};

//variabel global
Pasien  daftarPasien[MAX_PASIEN];
int     jumlahPasien = 0;

Dokter  daftarDokter[MAX_DOKTER];
int     jumlahDokter = 0;

int konterPasien  = 1;
int konterRekam   = 1;

//  deklarasi
void simpanFile();
void tampilPasien(const Pasien& p);
void tambahRekam(Pasien* p);
void tampilRiwayat(const Pasien* p);
void navMundur(const Pasien* p);
void hapusPasien();




string tglNow() {
    time_t t = time(nullptr);
    tm* lt   = localtime(&t);
    ostringstream oss;
    oss << setw(2) << setfill('0') << lt->tm_mday << "/"
        << setw(2) << setfill('0') << (lt->tm_mon + 1) << "/"
        << (lt->tm_year + 2000);
    return oss.str();
}

string genNoPasien() {
    ostringstream oss;
    oss << "P" << setw(4) << setfill('0') << konterPasien++;
    return oss.str();
}

string genNoRekam() {
    ostringstream oss;
    oss << "RM" << setw(5) << setfill('0') << konterRekam++;
    return oss.str();
}

void garis(char c = '=', int n = 60) {
    for (int i = 0; i < n; i++) cout << c;
    cout << "\n";
}

void header(const string& judul) {
    garis('=');
    int spasi = (60 - (int)judul.size()) / 2;
    if (spasi < 0) spasi = 0;
    cout << string(spasi, ' ') << judul << "\n";
    garis('=');
}

string toLower(string s) {
    for (size_t i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}

// akun - file
void simpanAkun() {
    ofstream f(FILE_AKUN);
    f << jumlahAkun << "\n";
    for (int i = 0; i < jumlahAkun; i++)
        f << daftarAkun[i].username << "|"
          << daftarAkun[i].password << "|"
          << daftarAkun[i].role     << "\n";
    f.close();
}

void muatAkun() {
    ifstream f(FILE_AKUN);
    if (!f.is_open()) return;
    f >> jumlahAkun; f.ignore();
    for (int i = 0; i < jumlahAkun; i++) {
        string line; getline(f, line);
        istringstream ss(line);
        getline(ss, daftarAkun[i].username, '|');
        getline(ss, daftarAkun[i].password, '|');
        getline(ss, daftarAkun[i].role,     '|');
    }
    f.close();
}

// Tambah akun baru
bool tambahAkun(const string& user, const string& pass, const string& role) {
    if (jumlahAkun >= MAX_AKUN) return false;
    // cek duplikat
    
    for (int i = 0; i < jumlahAkun; i++)
        if (daftarAkun[i].username == user) return false;
    daftarAkun[jumlahAkun++] = {user, pass, role};
    simpanAkun();
    return true;
}

Akun* cariAkun(const string& user) {
    for (int i = 0; i < jumlahAkun; i++)
        if (daftarAkun[i].username == user) return &daftarAkun[i];
    return nullptr;
}

//  regis akun 

void regAkun() {
    header("REGISTRASI AKUN BARU");
    if (!akunAktif || akunAktif->role != "admin") {
        cout << "  Hanya admin yang dapat mendaftarkan akun baru.\n";
        return;
    }

    string user, pass, role;
    cin.ignore();
   
    cout << "  Username baru   : "; getline(cin, user);
    if (user.empty())
     { 
		 cout << "  ! Username tidak boleh kosong !\n"; 
		return; 
		}

    cout << "  Password baru   : "; 
    getline(cin, pass);
    if (pass.empty())
     { 
		cout << "  ! Password tidak boleh kosong !\n";
		  return; 
		  }

    cout << "  Role (admin/petugas): ";
     getline(cin, role);
    if (role != "admin" && role != "petugas") role = "petugas";

    if (tambahAkun(user, pass, role)) {
        cout << "   Akun [" << user << "] berhasil didaftarkan sebagai " << role << ".\n";
    } else {
        cout << "   Gagal! Username sudah digunakan atau kapasitas penuh.\n";
    }
}


void tambahDokter(const string& id, const string& nama, const string& spesialis) 
{
    if (jumlahDokter >= MAX_DOKTER) return;
    daftarDokter[jumlahDokter++] = {id, nama, spesialis};
}

Dokter* cariDokter(const string& id) {
    for (int i = 0; i < jumlahDokter; i++)
        if (daftarDokter[i].id == id) return &daftarDokter[i];
    return nullptr;
}

void tampilDokter() {
    header("DAFTAR DOKTER");
    cout << left << setw(8) << "ID"
         << setw(25) << "Nama"
         << setw(20) << "Spesialisasi" << "\n";
    garis('-');
    for (int i = 0; i < jumlahDokter; i++) {
        cout << left << setw(8)  << daftarDokter[i].id
             << setw(25) << daftarDokter[i].nama
             << setw(20) << daftarDokter[i].spesialisasi << "\n";
    }
    garis('-');
}

//  pasien
Pasien* cariByNo(const string& no) {
    for (int i = 0; i < jumlahPasien; i++)
        if (daftarPasien[i].noPasien == no) return &daftarPasien[i];
    return nullptr;
}
Pasien* cariByNama(const string& nama) {
    string target = toLower(nama);
    for (int i = 0; i < jumlahPasien; i++)
        if (toLower(daftarPasien[i].nama).find(target) != string::npos)
            return &daftarPasien[i];
    return nullptr;
}

void tambahPasien() {
    if (jumlahPasien >= MAX_PASIEN) { cout << "  Kapasitas penuh.\n"; return; }
    Pasien& p  = daftarPasien[jumlahPasien];
    p.noPasien = genNoPasien();
    p.headRekam = p.tailRekam = nullptr;
    p.dokterPenangani = nullptr;

    cin.ignore();
    cout << "  Nama lengkap      : "; 
    getline(cin, p.nama);
    cout << "  Jenis kelamin(L/P): "; 
    getline(cin, p.jenisKelamin);
    cout << "  Tanggal lahir     : "; 
    getline(cin, p.tanggalLahir);
    cout << "  Alamat            : "; 
    getline(cin, p.alamat);
    cout << "  No. telepon       : "; 
    getline(cin, p.noTelp);

    jumlahPasien++;
    simpanFile();
    cout << "\n  Pasien terdaftar.\n Nomor Rekam Medis: " << p.noPasien << "\n";

    // pilihan dalam menu rekam medis 
    Pasien* ptr = &daftarPasien[jumlahPasien - 1];
    tampilPasien(*ptr);
    int c;
    do {
        cout << "  1. Tambah rekam medis baru\n";
        cout << "  2. Lihat riwayat (lama => baru)\n";
        cout << "  3. Lihat riwayat (baru => lama)\n";
        cout << "  0. Kembali ke menu utama\n";
        cout << "  Pilihan: "; cin >> c;
        switch (c) {
            case 1: tambahRekam(ptr);         break;
            case 2: tampilRiwayat(ptr);  break;
            case 3: navMundur(ptr);      break;
            case 0:                                break;
            default: cout << "  Pilihan tidak ada!.\n"; break;
        }
        cout << "\n";
    } while (c != 0);
}

void tampilPasien(const Pasien& p) {
    garis('-');
    cout << "  No. Rekam Medis : " << p.noPasien      << "\n";
    cout << "  Nama            : " << p.nama           << "\n";
    cout << "  Jenis Kelamin   : " << p.jenisKelamin   << "\n";
    cout << "  Tanggal Lahir   : " << p.tanggalLahir   << "\n";
    cout << "  Alamat          : " << p.alamat          << "\n";
    cout << "  No. Telepon     : " << p.noTelp          << "\n";
   
    garis('-');
}

void tampilSemua() {
    header("DATA SEMUA PASIEN");

    if (jumlahPasien == 0) {
        cout << "  Belum ada data pasien.\n";
        return;
    }

    cout << left
         << setw(8)  << "No.RM"
         << setw(25) << "Nama"
         << setw(6)  << "JK"
         << setw(15) << "No. Telepon"
         << "\n";

    garis('-', 55);

    for (int i = 0; i < jumlahPasien; i++) {

        cout << left
             << setw(8)  << daftarPasien[i].noPasien
             << setw(25) << daftarPasien[i].nama
             << setw(6)  << daftarPasien[i].jenisKelamin
             << setw(15) << daftarPasien[i].noTelp
             << "\n";
    }

    garis('-', 55);
}

//LL ganda

void tambahRekam(Pasien* p) {
    if (!p) return;
    string noRM = genNoRekam();
    string tgl  = tglNow();
    string kel, dia, obat;
    cin.ignore();
    cout << "  Keluhan          : ";
     getline(cin, kel);
    cout << "  Diagnosa         : "; 
    getline(cin, dia);
    cout << "  Resep obat       : "; 
    getline(cin, obat);

    tampilDokter();
    cout << "  Pilih ID dokter  : ";
    string idDok; getline(cin, idDok);
    Dokter* dok = cariDokter(idDok);
    if (dok) {
        p->dokterPenangani = dok;
        cout << "   Dokter: " << dok->nama << " (" << dok->spesialisasi << ")\n";
    } else {
        cout << "  ID dokter tidak ditemukan, dokter tidak diubah.\n";
    }
    idDok = p->dokterPenangani ? p->dokterPenangani->id : "-";

    NodeRekamMedis* node = new NodeRekamMedis(noRM, tgl, kel, dia, obat, idDok);
    if (!p->headRekam) {
        p->headRekam = p->tailRekam = node;
    } else {
        node->prev = p->tailRekam;
        p->tailRekam->next = node;
        p->tailRekam = node;
    }
    cout << "   Rekam medis tersimpan.\n No: " << noRM << "\n";
    simpanFile();
}

void tampilRiwayat(const Pasien* p) {
    if (!p) return;
    header("RIWAYAT REKAM MEDIS: " + p->nama);
    if (!p->headRekam) { cout << "  Belum ada riwayat.\n"; return; }
    NodeRekamMedis* cur = p->headRekam;
    int urut = 1;
    while (cur) {
        Dokter* d = cariDokter(cur->idDokter);
        cout << "  [" << urut++ << "] " << cur->noRekam
             << "  Tgl: " << cur->tanggal << "\n";
        cout << "      Keluhan  : " << cur->keluhan  << "\n";
        cout << "      Diagnosa : " << cur->diagnosa << "\n";
        cout << "      Obat     : " << cur->obat     << "\n";
        cout << "      Dokter   : " << (d ? d->nama : cur->idDokter) << "\n";
        garis('-', 45);
        cur = cur->next;
    }
}

void navMundur(const Pasien* p) {
    if (!p || !p->tailRekam) { cout << "  Belum ada riwayat.\n"; return; }
    header("RIWAYAT (TERBARU -> LAMA)");
    NodeRekamMedis* cur = p->tailRekam;
    int urut = 1;
    while (cur) {
        cout << "  [" << urut++ << "] " << cur->noRekam
             << "  " << cur->tanggal
             << "  Diagnosa: " << cur->diagnosa << "\n";
        cur = cur->prev;
    }
}

//sorting

void sortAsc() {
    for (int i = 0; i < jumlahPasien - 1; i++) {

        for (int j = 0; j < jumlahPasien - i - 1; j++) {

            if (toLower(daftarPasien[j].nama) >
                toLower(daftarPasien[j + 1].nama)) {

                Pasien temp = daftarPasien[j];
                daftarPasien[j] = daftarPasien[j + 1];
                daftarPasien[j + 1] = temp;
            }
        }
    }

    cout << "  Diurutkan A-Z (ascending).\n";
}

void sortDesc() {
    for (int i = 0; i < jumlahPasien - 1; i++) {

        for (int j = 0; j < jumlahPasien - i - 1; j++) {

            if (toLower(daftarPasien[j].nama) <
                toLower(daftarPasien[j + 1].nama)) {

                Pasien temp = daftarPasien[j];
                daftarPasien[j] = daftarPasien[j + 1];
                daftarPasien[j + 1] = temp;
            }
        }
    }

    cout << "  Diurutkan Z-A (descending).\n";
}

void menuSort() {
    header("URUTKAN PASIEN");
    cout << "  [1] Urutkan A-Z (ascending)\n";
    cout << "  [2] Urutkan Z-A (descending)\n";
    cout << "  [0] Kembali\n";
    cout << "  Pilihan: "; int c; cin >> c;
    switch (c) {
        case 1: sortAsc();  tampilSemua(); break;
        case 2: sortDesc(); tampilSemua(); break;
        case 0: cout << "  Kembali ke menu utama.\n"; break;
        default: cout << "  Pilihan tidak valid.\n"; break;
    }
}


//searching

void cariNama(const string& keyword) {
    string target = toLower(keyword);
    int jumlahHasil = 0;

    cout << "\n  [Sequential Search] Kata kunci nama: \"" << keyword << "\"\n";
    cout << "  Memeriksa " << jumlahPasien << " data pasien satu per satu...\n";
    garis('-');
    cout << left << setw(8)  << "No.RM"
                 << setw(25) << "Nama"
                 << setw(6)  << "JK"
                 << setw(15) << "No. Telepon"
                 << setw(20) << "Dokter" << "\n";
    garis('-');

    for (int i = 0; i < jumlahPasien; i++) {          // iterasi satu per satu
        if (toLower(daftarPasien[i].nama).find(target) != string::npos) {
            cout << left
                 << setw(8)  << daftarPasien[i].noPasien
                 << setw(25) << daftarPasien[i].nama
                 << setw(6)  << daftarPasien[i].jenisKelamin
                 << setw(15) << daftarPasien[i].noTelp
                 << setw(20) << (daftarPasien[i].dokterPenangani
                                    ? daftarPasien[i].dokterPenangani->nama : "-")
                 << "\n";
            jumlahHasil++;
        }
    }
    garis('-');
    cout << "  Total ditemukan : " << jumlahHasil << " pasien.\n";

    if (jumlahHasil == 0) {
        cout << "  Pasien dengan nama \"" << keyword << "\" tidak ditemukan.\n";
        return;
    }

    // Jika hanya 1 hasil, langsung tampilkan detail
    if (jumlahHasil == 1) {
        Pasien* p = cariByNama(keyword);
        if (p) {
            cout << "\n  Detail pasien:\n";
            tampilPasien(*p);
        }
    } else {
        // Jika lebih dari 1, minta No. RM untuk lihat detail
        cout << "\n  Masukkan No. Rekam Medis untuk melihat detail : ";
        string no; getline(cin, no);
        if (!no.empty()) {
            Pasien* p = cariByNo(no);
            if (p)  tampilPasien(*p);
            else    cout << "  No. Rekam Medis tidak ditemukan.\n";
        }
    }
}

// Sequential Search berdasarkan No. Rekam Medis — mencari kecocokan tepat
void cariNomor(const string& keyword) {
    cout << "\n  [Sequential Search] No. Rekam Medis: \"" << keyword << "\"\n";
    cout << "  Memeriksa " << jumlahPasien << " data pasien satu per satu...\n";
    garis('-');

    for (int i = 0; i < jumlahPasien; i++) {          // iterasi satu per satu
        if (daftarPasien[i].noPasien == keyword) {
            cout << "  Ditemukan pada indeks ke-" << i << ".\n";
            tampilPasien(daftarPasien[i]);
            return;                                    // berhenti setelah menemukan
        }
    }

    // Jika seluruh data sudah diperiksa dan tidak ada yang cocok
    cout << "  No. Rekam Medis \"" << keyword << "\" tidak ditemukan.\n";
}

void menuCari() {
    header("PENCARIAN PASIEN (SEQUENTIAL SEARCH)");
    if (jumlahPasien == 0) { cout << "  Belum ada data pasien.\n"; return; }

    cout << "  [1] Cari berdasarkan Nama\n";
    cout << "  [2] Cari berdasarkan No. Rekam Medis\n";
    cout << "  [0] Kembali\n";
    cout << "  Pilihan: ";
    int p; cin >> p; cin.ignore();

    string kw;
    switch (p) {
        case 1:
            cout << "  Masukkan nama   : "; getline(cin, kw);
            cariNama(kw);
            break;
        case 2:
            cout << "  Masukkan No. RM : "; getline(cin, kw);
            cariNomor(kw);
            break;
        case 0:
            cout << "  Kembali ke menu utama.\n";
            break;
        default:
            cout << "  Pilihan tidak valid.\n";
            break;
    }
}


//  file 

void simpanFile() {
    ofstream fd(FILE_DOKTER);
    fd << jumlahDokter << "\n";
    for (int i = 0; i < jumlahDokter; i++)
        fd << daftarDokter[i].id   << "|"
           << daftarDokter[i].nama << "|"
           << daftarDokter[i].spesialisasi << "\n";
    fd.close();

    ofstream fp(FILE_PASIEN);
    fp << jumlahPasien << "\n" << konterPasien << "\n";
    for (int i = 0; i < jumlahPasien; i++) {
        Pasien& p = daftarPasien[i];
        fp << p.noPasien     << "|" << p.nama         << "|"
           << p.jenisKelamin << "|" << p.tanggalLahir << "|"
           << p.alamat       << "|" << p.noTelp       << "|"
           << (p.dokterPenangani ? p.dokterPenangani->id : "-") << "\n";
    }
    fp.close();

    ofstream fr(FILE_REKAM);
    fr << konterRekam << "\n";
    for (int i = 0; i < jumlahPasien; i++) {
        NodeRekamMedis* cur = daftarPasien[i].headRekam;
        while (cur) {
            fr << daftarPasien[i].noPasien << "|"
               << cur->noRekam  << "|" << cur->tanggal  << "|"
               << cur->keluhan  << "|" << cur->diagnosa << "|"
               << cur->obat     << "|" << cur->idDokter << "\n";
            cur = cur->next;
        }
    }
    fr.close();
    cout << "   Data berhasil disimpan.\n";
}

void muatFile() {
    ifstream fd(FILE_DOKTER);
    if (fd.is_open()) {
        fd >> jumlahDokter; fd.ignore();
        for (int i = 0; i < jumlahDokter; i++) {
            string line; getline(fd, line);
            istringstream ss(line);
            getline(ss, daftarDokter[i].id,           '|');
            getline(ss, daftarDokter[i].nama,         '|');
            getline(ss, daftarDokter[i].spesialisasi, '|');
        }
        fd.close();
    }

    ifstream fp(FILE_PASIEN);
    if (fp.is_open()) {
        fp >> jumlahPasien >> konterPasien; fp.ignore();
        for (int i = 0; i < jumlahPasien; i++) {
            string line; getline(fp, line);
            istringstream ss(line);
            Pasien& p = daftarPasien[i];
            string idDok;
            getline(ss, p.noPasien,     '|');
            getline(ss, p.nama,         '|');
            getline(ss, p.jenisKelamin, '|');
            getline(ss, p.tanggalLahir, '|');
            getline(ss, p.alamat,       '|');
            getline(ss, p.noTelp,       '|');
            getline(ss, idDok,          '|');
            p.dokterPenangani = cariDokter(idDok);
            p.headRekam = p.tailRekam = nullptr;
        }
        fp.close();
    }

    ifstream fr(FILE_REKAM);
    if (fr.is_open()) {
        fr >> konterRekam; fr.ignore();
        string line;
        while (getline(fr, line)) {
            istringstream ss(line);
            string noPas, noRM, tgl, kel, dia, obat, idDok;
            getline(ss, noPas,  '|');
            getline(ss, noRM,   '|');
            getline(ss, tgl,    '|');
            getline(ss, kel,    '|');
            getline(ss, dia,    '|');
            getline(ss, obat,   '|');
            getline(ss, idDok,  '|');
            Pasien* p = cariByNo(noPas);
            if (p) {
                NodeRekamMedis* node = new NodeRekamMedis(noRM,tgl,kel,dia,obat,idDok);
                if (!p->headRekam) { p->headRekam = p->tailRekam = node; }
                else { node->prev = p->tailRekam; p->tailRekam->next = node; p->tailRekam = node; }
            }
        }
        fr.close();
    }
    cout << "  Data berhasil dimuat dari file.\n";
}

// Hapus pasien beserta rekam medisnya (hanya admin)
void hapusPasien() {
    header("HAPUS DATA PASIEN");

    if (!akunAktif || akunAktif->role != "admin") {
        cout << "  Akses ditolak! Hanya admin yang dapat menghapus data pasien!\n";
        return;
    }

    if (jumlahPasien == 0) {
        cout << "  Belum ada data pasien.\n";
        return;
    }

    cin.ignore();
    cout << "  Masukkan No. Rekam Medis pasien yang akan dihapus: ";
    string no; getline(cin, no);

    // Cari indeks pasien
    int idx = -1;
    for (int i = 0; i < jumlahPasien; i++) {
        if (daftarPasien[i].noPasien == no) { idx = i; break; }
    }

    if (idx == -1) {
        cout << "  Pasien dengan No. RM \"" << no << "\" tidak ditemukan.\n";
        return;
    }

    // Tampilkan data sebelum konfirmasi
    tampilPasien(daftarPasien[idx]);
    cout << "  Yakin ingin menghapus pasien ini? (y/n): ";
    string konfirm; getline(cin, konfirm);
    if (konfirm != "y" && konfirm != "Y") {
        cout << "  Penghapusan dibatalkan.\n";
        return;
    }

    // Bebaskan semua node rekam medis (linked list)
    NodeRekamMedis* cur = daftarPasien[idx].headRekam;
    while (cur) {
        NodeRekamMedis* next = cur->next;
        delete cur;
        cur = next;
    }

    // Geser array ke kiri untuk menutup slot yang dihapus
    for (int i = idx; i < jumlahPasien - 1; i++) {
        daftarPasien[i] = daftarPasien[i + 1];
    }
    jumlahPasien--;

    // Simpan perubahan ke file
    simpanFile();
    cout << "  Pasien dengan No. RM \"" << no << "\" berhasil dihapus.\n";
}

//inisialisasi daftar dokter
void initDokter() {
    Dokter data[] = {
        {"D001", "dr. Andi Santoso", "Umum"},
        {"D002", "dr. Budi Hartono", "Penyakit Dalam"},
        {"D003", "dr. Citra Dewi", "Kandungan"},
        {"D004", "dr. Dian Pratama", "Bedah"},
        {"D005", "dr. Hadi Wijaya", "THT"},
        {"D006", "dr. Gina Putri", "Mata"},
        {"D007", "dr. Joko Saputra", "Jantung"},
        {"D008", "dr. Taufik Hidayat", "Psikiatri"},
        {"D009", "dr. Rian Saputra", "Radiologi"},
        {"D010", "dr. Olivia Putri", "Gizi"}

    };
  int jumlahData = sizeof(data) / sizeof(data[0]);

for (int i = 0; i < jumlahData; i++) {
    daftarDokter[jumlahDokter++] = data[i];
}
}

//  menu rekam medis

void menuRekam() {
    cout << "MENU REKAM MEDIS\n";
  
    cout << "  No. Rekam Medis pasien: "; string no; cin >> no;
    Pasien* p = cariByNo(no);
    if (!p) { cout << "   Pasien tidak ditemukan.\n"; return; }
    tampilPasien(*p);

    int c;
    do {
        cout << "  [1] Tambah rekam medis baru\n";
        cout << "  [2] Lihat riwayat (lama -> baru)\n";
        cout << "  [3] Lihat riwayat (baru -> lama)\n";
        cout << "  [0] Kembali\n";
        cout << "  Pilihan: "; cin >> c;
        switch (c) {
            case 1: tambahRekam(p);        break;
            case 2: tampilRiwayat(p); break;
            case 3: navMundur(p);     break;
            case 0:                             break;
            default: cout << "  Pilihan tidak valid.\n"; break;
        }
        cout << "\n";
    } while (c != 0);
}

//Login
bool login() {
    int sisa = MAX_LOGIN;
    while (sisa > 0) {
        string user, pass;
        cin.ignore();
        cout << "  Username : "; getline(cin, user);
        cout << "  Password : "; getline(cin, pass);

        Akun* akun = cariAkun(user);
        if (akun && akun->password == pass) {
            cout << "\n   Login berhasil! Selamat datang, "
                 << akun->username << " [" << akun->role << "]\n\n";
            akunAktif = akun;
            return true;
        }

        sisa--;
        if (sisa > 0) {
            cout << "\n   Username atau password salah!"
                 << " Kesempatan tersisa: " << sisa << "\n";
            garis('-');
            cout << "  [1]  Coba lagi\n";
            cout << "  [0]  Kembali ke menu utama\n";
            garis('-');
            cout << "  Pilihan: ";
            string pilLogin; getline(cin, pilLogin);
            if (pilLogin == "0") {
                cout << "\n";
                return false;
            }
            cout << "\n";
        }
    }
    cout << "\n   Kesempatan login Anda habis. Akses ditolak.\n";
    return false;
}

void regBaru() {
    header("REGISTRASI AKUN BARU");
    string user, pass, pass2;
    cin.ignore();
    cout << "  Username baru    : "; getline(cin, user);
    if (user.empty()) { cout << "   Username tidak boleh kosong.\n"; return; }
    if (cariAkun(user)) { cout << "   Username sudah digunakan.\n"; return; }

    cout << "  Password         : "; getline(cin, pass);
    if (pass.empty()) { cout << "   Password tidak boleh kosong.\n"; return; }

    cout << "  Konfirmasi pass  : "; getline(cin, pass2);
    if (pass != pass2) { cout << "   Password tidak cocok.\n"; return; }

//jika blm ada akun = admin, sisanya as petugas
    string role = (jumlahAkun == 0) ? "admin" : "petugas";

    if (tambahAkun(user, pass, role)) {
        cout << "   Akun [" << user << "] berhasil dibuat"
             << " sebagai " << role << ".\n";
    } else {
        cout << "   Gagal membuat akun.\n";
    }
}

//  MAIN
int main() {
    muatAkun();
    initDokter();

    int pilAwal;
    
    do {
        header("SISTEM REKAM MEDIS KLINIK");
        cout << "  1.  Registrasi Akun\n";
        cout << "  2.  Login\n";
        cout << "  3.  Keluar\n";
        garis('-');
        cout << "  Pilihan: ";
        cin >> pilAwal;

        switch (pilAwal) {
            case 1:
                regBaru();
                cout << "\n";
                break;

            case 2:
            system("cls");
            
                header("LOGIN");
                if (!login()) {
                    cout << "\n";
                    break;
                }

                muatFile();
                
         {
           int pilihan;
           do {
           header("MENU UTAMA");
           cout << "  Login  : " << akunAktif->username
               << " [" << akunAktif->role << "]\n";
                garis('-');
           cout << "  1.  Daftar Pasien Baru\n";
           cout << "  2.  Tampilkan Semua Pasien\n";
           cout << "  3.  Cari Pasien\n";
           cout << "  4.  Menu Rekam Medis\n";
           cout << "  5.  Urutkan Pasien\n";
           cout << "  6.  Tampilkan Daftar Dokter\n";
           if (akunAktif && akunAktif->role == "admin")
               cout << "  8.  Hapus Data Pasien [ADMIN]\n";
           cout << "  7.  Logout\n";
           cout << "  0.  Keluar Program\n";
           garis();
               cout << "  Masukkan Pilihan: ";
               cin >> pilihan;

                        switch (pilihan) {
                            case 1: tambahPasien();
                             break;
                            case 2: tampilSemua(); 
                            break;
                            case 3: menuCari();
                             break;
                            case 4: menuRekam();
                             break;
                            case 5: menuSort(); 
                            break;
                            case 6: tampilDokter(); 
                            break;

                            case 8: hapusPasien();
                            break;

                            case 7:
                                simpanFile();
                                akunAktif = nullptr;
                                cout << "\n  Logout berhasil.\n\n";
                                break;

                            case 0:
                                simpanFile();
                                cout << "\n  Program selesai.\n\n";
                                return 0;

                            default:
                                cout << "  Pilihan tidak valid.\n";
                                break;
                        }

                        cout << "\n";

                    } while (pilihan != 7);
                }
                break;

            case 3:
                cout << "\n  Terima kasih. Program ditutup.\n\n";
                return 0;

            default:
                cout << "  Pilihan tidak valid.\n\n";
                break;
        }

    } while (pilAwal != 3);

    return 0;
}
