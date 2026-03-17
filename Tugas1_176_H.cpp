#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct produk{
	char name[60];
	char category[30];
	double price;
	int stock;
	float rating;
	};
	
	produk katalog[200];
	int n=0;
	
void muatFile(){
	FILE *shop;
	shop = fopen("shopease_db.txt", "r");
	
	if(shop == NULL){
		return;
		}
	
		while(fscanf(shop, " %[^|]|%[^|]|%lf|%d|%f\n", 
		katalog[n].name,
		katalog[n].category, 
		&katalog[n].price, 
		&katalog[n].stock, 
		&katalog[n].rating) !=EOF){
			n++;
			}
			fclose(shop);
	}
	
void simpanFile(){
		FILE *shop;
		shop = fopen ("shopease_db.txt", "w");
		
		for(int i=0; i<n; i++) {
			fprintf(shop, "%s|%s|%.01f|%d|%.1f\n", katalog[i].name,
			katalog[i].category, katalog[i].price, katalog[i].stock, 
			katalog[i].rating);
			}
			fclose(shop);
		}
		

		
void tambahProduk(){
	cout << "\tTAMBAH PRODUK BARU\t"<<endl;
	cout << "==================================="<<endl;
	cin.ignore();
	
	cout << "Nama Produk: ";
	cin.getline(katalog[n].name,60);
	cout << "Kategori: ";
	cin.getline(katalog[n].category,30);
	cout << "Harga: ";
	cin >> katalog[n].price;
	cout << "Stok: ";
	cin >> katalog[n].stock;
	cout <<"Rating: ";
	cin >> katalog[n].rating;
	n++;
	simpanFile();
	cout <<endl;
	cout <<"===================================\n";
	cout <<"Produk Berhasil Ditambahkan\n";
	}
	
void bubbleSort(){
	for(int i=0; i<n-i-1; i++){
		for(int j=0; j<n-i-1; j++){
			if(strcmp(katalog[j].name, katalog[j+1].name) >0){
				produk temp = katalog[j];
				katalog[j] = katalog[j+1];
				katalog[j+1] = temp;
				}
			}
		}
	}
		
int tengah(int low, int high){
	float pivot = katalog[high].rating;
	int i = low-1;
	
	for(int j=low; j<high; j++){
		if(katalog[j].rating > pivot){
		i++;
		produk temp = katalog[i];
		katalog[i] = katalog[j];
		katalog[j] = temp;
		}
	}
		produk temp = katalog[i+1];
		katalog[i+1] = katalog[high];
		katalog[high] = temp;
		
		return i+1;
	}
	
void quickSort(int low, int high){
	if(low<high){
		
		int pi = tengah(low, high);
		quickSort(low, pi-1);
		quickSort(pi+1, high);
		}
	}
	
void tampilProduk(){
	int pilih;
	
	cout << "\nMODE TAMPILAN\n";
	cout << "============================\n";
	cout << "1. Nama Produk(Asc)\n";
	cout << "2. Rating Produk(Desc)\n";
	cout << "Pilih: ";
	cin  >> pilih;
	
	if(pilih == 1){
		
		bubbleSort();
		}
		else if(pilih == 2){
			quickSort(0, n-1);
			}
			
		cout << "\n============================================= DAFTAR PRODUK ============================================\n";
		cout << "========================================================================================================\n";
		cout << "No\t| \tNama Produk\t| \tKategori\t|\tHarga\t|\tStok\t|\tRating\t|\n";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		
		for(int i=0; i<n; i++){
			cout << i+1 <<"\t|" << katalog[i].name<<" \t\t|"<<katalog[i].category<<" \t\t|"<<katalog[i].price<< " \t\t|"<<katalog[i].stock<<" \t\t|"<<katalog[i].rating<<" \t\t|"<<endl;
			}
			cout <<  "_________________________________________________________________________________________________________";
	}
	
void cariProduk(){
	char cari[60];
	bool found= false;
	
	cin.ignore();
	cout << "CARI PRODUK\n";
	cout << "=============================\n";
	cout << "\nMasukkan Nama Produk : ";
	cin.getline(cari,60);
	
	for(int i=0; i<n; i++){
		if(strcmp(cari, katalog[i].name) == 0){
			cout<<endl;
			cout<<"Nama Produk: "<<katalog[i].name <<endl;
			cout <<"Kategori: "<< katalog[i].category<<endl;
			cout <<"Harga: "<<katalog[i].price <<endl;
			cout <<"Stok: "<<katalog[i].stock <<endl;
			cout <<"Rating: "<< katalog[i].rating<<endl;
			
			found = true;
			break;
			}
		}
		if(!found){
			cout << "!!Produk Tidak Ditemukan!!\n";
			}
	}
	
int main(){
	int pilihan;
	char kembali;
	muatFile();
	
	do{
		system("cls");
		cout << "|----------------------------------------|\n";
		cout << "|\tSHOPEASE E-CATALOG\t\t |\n";
		cout << "|========================================|\n";
		cout << "|1. Tambah Produk Baru\t\t\t |"<<endl;
		cout << "|2. Tampilkan Daftar Produk\t\t |"<<endl;
		cout << "|3. Cari Produk\t\t\t\t |"<<endl;
		cout << "|4. Keluar dan Simpan\t\t\t |"<<endl;
		cout << "|----------------------------------------|";
		cout <<endl;
		cout << "  Pilih Menu: ";
		cin >> pilihan;
		
		system("cls");
		
		switch(pilihan){
			case 1: tambahProduk();
			break;
			case 2: tampilProduk();
			break;
			case 3: cariProduk();
			break;
			case 4: simpanFile();
				cout << "---------------------------------------------------------";
				cout << "\n|Data Telah Disimpan.\t\t\t\t\t|";
				cout<< "\n|Terima Kasih Telah Menggunakan ShopEase. Sampai Jumpa! |\n ";
				cout << "--------------------------------------------------------";
				return 0;
			default:
			cout <<"Maaf, Menu yang Anda Pilih Tidak Tersedia"<<endl;
			}
			cout << "\nKembali ke Menu? (Y/y): ";
			cin >> kembali;
		} while (kembali == 'Y' || kembali == 'y');
		simpanFile();
		cout << "\n Terima Kasih Telah Menggnakan ShopEase";
	}	

		
		
