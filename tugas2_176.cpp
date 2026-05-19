#include <iostream>
using namespace std;

int maxData = 100;

struct kendaraan{
	string nopol;
	string pemilik;
	string status;
};

struct Node {
	kendaraan data;
	Node* kiri;
	Node* kanan;
};

struct riwayat {
	string aksi;
	string nopol;
};

Node* root = nullptr;

int parkir = 50;
int jmlParkir = 0;

riwayat stackUndo[100];		
int top = -1;

string antrian[100]; 		
int depan = 0;
int belakang = -1;

//bst
Node* buatNode(string nopol, string pemilik) {
	Node* baru = new Node;
	
	baru->data.nopol = nopol;
	baru->data.pemilik = pemilik;
	baru->data.status = "Di luar Parkiran";
	
	baru->kiri = nullptr;
	baru->kanan = nullptr;
	return baru;
	}

Node* insertNode (Node* root, string nopol, string pemilik){
	if (root == nullptr) {
		cout<<endl;
		cout << " Kendaraan Berhasil Ditambahkan\n";
		return buatNode(nopol, pemilik);
		}
		
		if(nopol < root->data.nopol){
			root->kanan = insertNode(root->kanan, nopol, pemilik);
			}
			
			else if (nopol > root->data.nopol){
				root->kanan = insertNode(root->kanan, nopol, pemilik);
				}
	return root;
	}
	
Node* cariNode(Node* root, string nopol){
	if (root == nullptr){
		return nullptr;
		}
			if(nopol == root->data.nopol){
				return root;
				} 
					if (nopol < root->data.nopol){
						return cariNode(root->kiri, nopol);
						}
						return cariNode(root->kanan, nopol);
	}
void tampil (Node* root){
	if (root == nullptr){
		return;
		}
		tampil(root->kiri);
		cout << "Nomor Polisi : "<< root->data.nopol <<endl;
		cout << "Nama Pemilik : "<< root->data.pemilik <<endl;
		cout << "Status       : "<< root->data.status <<endl;
		cout << "===========================================\n";
		tampil(root->kanan);
		
	}

Node* cariMin(Node* root){	//utk cari nilai terkerkecil bst
	while (root->kiri !=nullptr) {
		root = root->kiri;
		}
		return root;
}

Node* hapusNode (Node* root, string nopol){
	if (root == nullptr){
		return nullptr;
		}
	if (nopol < root->data.nopol){
		root->kiri = hapusNode(root->kiri, nopol);
		}
		else if (nopol > root->data.nopol){
			root->kanan = hapusNode(root->kanan, nopol);
			}
			else {
				if (root->kiri == nullptr){
					Node* temp = root->kanan;
					delete root;
					return temp;
					}
					else if (root->kanan == nullptr){
						Node* temp = root->kiri;
						delete root;
						return temp;
						}
				Node* temp = cariMin(root->kanan);
				root->data = temp->data;
				root->kanan = hapusNode(root->kanan, temp->data.nopol);
				}
			return root;
	}
	
//stack
void pushUndo(string aksi, string nopol){
	top++;
	
	stackUndo[top].aksi = aksi;
	stackUndo[top].nopol = nopol;
}

bool stackKosong() {
	return top == -1;
	}

riwayat popUndo() {
	riwayat temp = stackUndo[top];
	top--;
	return temp;
	}

//queue
bool queueKosong() {
	return depan > belakang;
	}
void enqueue(string nopol){
	belakang++;
	antrian[belakang] = nopol;
	}

string dequeue() {
	string temp = antrian[depan];
	depan++;
	return temp;
	}

int jmlAntrian(){
	if(queueKosong()) {
		return 0;
		}
		return belakang - depan +1;
	}
	
void tambah(){
	string nopol, pemilik;
	
	cout << "\n Masukkan Nomor Polisi: ";
	cin.ignore();
	getline(cin, nopol);
	
	cout << "\n Masukkan Nama Pemilik: ";
	getline(cin, pemilik);
	
	root = insertNode(root, nopol, pemilik);
	}
	
void masuk(){
	string nopol;
	
	cout << "\n Masukkan Nomor Polisi: ";
	cin.ignore();
	getline(cin, nopol);
	
	Node* kendaraan = cariNode(root, nopol);
	
	if(kendaraan == nullptr){
		cout << "Kendaraan Tidak Ditemukan!\n";
		return;
		}
		if (jmlParkir < parkir) {
			kendaraan->data.status = "Di Parkiran";
			jmlParkir++;
			
			pushUndo("masuk", nopol);
			cout << "Kendaraan Berhasil Masuk\n";
			}
				else {
					cout << "Parkiran Penuh! Kendaraan Masuk Antrian!\n";
					}
	}
	
void keluar() {
	string nopol;
	
	cout << "\n Masukkan Nomor Polisi: ";
	cin.ignore();
	getline(cin, nopol);
	
	Node* kendaraan = cariNode(root, nopol);
	if (kendaraan == nullptr) {
		cout << "Kendaraan Tidak Ditemukan!\n";
		return;
		}
		if(kendaraan->data.status == "Di Luar Parkiran") {
			cout << "Kendaraan Tidak di Parkiran! \n";
			return;
			}
			kendaraan->data.status = "Di Luar Parkiran";
			jmlParkir--;
			
			pushUndo("Keluar", nopol);
			cout << "Kendaraan Berhasil Keluar\n";
			
			if(!queueKosong()) {
				string nextNopol = dequeue();
				Node* next = cariNode(root,nextNopol);
				
					if (next != nullptr){
						next->data.status = "Di Parkiran";
						jmlParkir++;
						
						cout << "Kendaraan berikutnya masuk dari antrian!\n";
						}
				}
	}

void hapus() {
	string nopol;
	
	cout << "\n Masukkan Nomor Polisi: ";
	cin.ignore();
	getline(cin, nopol);
	
	Node* cek = cariNode(root, nopol);
	
	if(cek == nullptr){
		cout << "Kendaraan Tidak Ditemukan!\n";
		return;
		
		}
		root = hapusNode(root, nopol);
		cout << "Data kendaraan berhasil dihapus!\n";
	}
	
void undoAksi(){
	if (stackKosong()){
		
		cout << "Tidak ada akdi untuk di-Undo!\n";
		return;
		}
		riwayat terakhir = popUndo();
		Node* kendaraan = cariNode(root, terakhir.nopol);
			if(kendaraan == nullptr){
				return;
				}
				if (terakhir.aksi == "masuk"){
					kendaraan->data.status = "Di Luar Parkiran";
					jmlParkir--;
					cout << "Undo: Kendaraan keluar dari parkiran\n";
					}
				else if (terakhir.aksi == "keluar"){
				kendaraan->data.status = "Di Parkiran";
				jmlParkir++;
				cout << "Undo: Kendaraan masuk kembali ke parkiran\n";
				}
	}

void tampilAntrian(){
	if(queueKosong()){
		cout << "\nAntrian Kosong\n";
		return;
		}
		cout << "\n====== DAFTAR ANTRIAN PARKIR =======\n";
		for (int i= depan; i <= belakang; i++){
			cout << i - depan + 1 << "."<< antrian[i] << endl;
			
			}
	}
	
int main(){
	int pilih;
	
	do{
		 cout << "\n-----------------------------------------------------\n";
    cout << "           SISTEM PARKIR INAP - BANDARA GSA         \n";
    cout << "=====================================================\n";
    cout << "Kapasitas Parkir : "<< parkir <<"\t| Terisi: "<<jmlParkir << "\t| Antrian: "<<jmlAntrian() <<endl;
    cout << "-----------------------------------------------------\n";
    cout << "1. Tambah Data Kendaraan\n";
    cout << "2. Tampilkan Semua Kendaraan\n";
    cout << "3. Catat Kendaraan Masuk\n";
    cout << "4. Catat Kendaraan Keluar\n";
    cout << "5. Hapus Data Kendaraan\n";
    cout << "6. Undo Aksi Terakhir\n";
    cout << "7. Tampilkan Antrian Parkir\n";
    cout << "0. Keluar\n";
    cout << endl;
    cout << "Pilihan: ";
    cin >>pilih;
    
    switch(pilih){
		case 1: tambah();
		break;
		case 2: 
			cout << "\n====== DATA KENDARAAN ======\n";
			if (root == nullptr) {
				cout << "Tidak Ada Kendaraan!\n";
				cout << endl;
				}
				else {
					tampil(root);
					}
				break;
		case 3: masuk();
		break;
		case 4: keluar();
		break;
		case 5: hapus();
		break;
		case 6: undoAksi();
		break;
		case 7: tampilAntrian();
		break;
		case 0:
			cout << "\n Program Selesai. Terima Kasih\n";
			break;
		default:
		cout << "\n Menu Tidak Tersedia!\n";
		}
		}while (pilih !=0);
	return 0;
	}
