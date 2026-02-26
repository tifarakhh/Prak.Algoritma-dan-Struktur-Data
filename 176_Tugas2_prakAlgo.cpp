#include <iostream>
using namespace std;

struct Buku {
	int no;
	string nama;
	int harga;
	};
	
	void Sequential (Buku daftar [], int n, int cari) {
		bool found = false;
		for (int i=0; i<n; i++) {
			if (daftar[i].no == cari) {
		cout << " Buku " << daftar [i].nama << " Ditemukan" << endl;
		cout << " Harga: Rp. " <<daftar[i].harga << endl;
		found = true;
		}
	}
	if (!found) { 
		cout << "Buku nomor " << cari << "tidak ditemukan" <<endl;
			}

		}
		
		void Binary (Buku daftar[], int n, int cari ) {
			int i=0;
			int j= n-1;
			bool found = false;
			
			while (i<= j) {
				int k = (i+j) / 2; 
					if (daftar[k].no == cari) {
						cout << "Buku " << daftar[k].nama << " Ditemukan" << endl;
						cout << "Harga: Rp." << daftar[k].harga << endl;
						found = true;
						break;
						}
						else if (daftar[k].no <cari) { 
							i= k+1;
							 }
							
							else {
								j= k-1;
							
							 }
								}
							
			
		if (!found) {
			cout << "Buku nomor "<< cari << "tidak ditemukan";
		}
	}
		
	int main () {
		int jmlbuku = 5;
		Buku daftar[5] = {
			{1, "Laskar Pelangi", 75000},
			{2, "Janji", 67000},
			{3, "Laut Bercerita", 79000},
			{4, "Hello", 64000},
			{5, "Perahu Kertas", 62000}
		};
		
		cout << " \tDAFTAR BUKU\t "<< endl;
		for (int i=0; i < jmlbuku; i++) {
			cout << daftar[i].no << ". " << daftar[i].nama<<endl;
		}
		cout << "\t======================\t"<< endl;
		
		int nomorCari;
		int pilih;
		
		cout << "Masukkan nomor buku yang dicari: ";
		cin >> nomorCari;
		
		cout << "Metode pencarian: " <<endl;
		cout << "1. Pencarian Sequential" <<endl;
		cout << "2. Pencarian Binary " << endl;
		cout << "Pilih (1/2): ";
		cin >> pilih;
		
			if (pilih == 1) {
				Sequential (daftar, jmlbuku, nomorCari);
				}else if (pilih ==2) {
					Binary (daftar, jmlbuku, nomorCari);
			} else
			 { cout << "Pilihan Tidak Ada" <<endl;
			}
		
		}
		
					
					
					
					

					
