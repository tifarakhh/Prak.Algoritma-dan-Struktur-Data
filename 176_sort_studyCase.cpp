#include <iostream>
using namespace std;

void bubbleSort(string array[], int n){
	for(int i= 0; i<n-1; i++){
		for(int j=0; j< n-i-1; j++){
			if (array[j] > array[j+1]){
				string temp = array[j];
				array[j] = array [j+1];
				array [j+1]= temp;
				}
			}
		}
 }
 
 int tengah (string array[], int low, int high) {
	 string pivot = array[high];
	 int i = low - 1;
	 for (int j = low; j< high; j++){
		 if(array [i]> pivot){
			 i++;
			 swap (array[i], array[j]);
	 }
 }
 swap (array [i+1], array [high]);
 return i+1;
}
 void quickSort(string array[], int low, int high){
 if (low< high) {
 int ti = tengah(array, low, high);
 quickSort(array, low, ti-1);
 quickSort(array, ti+1, high);
	}
 }

void tampilData(string array[], int n){
	for (int i = 0; i<n; i++) {
	cout << i+1 << "." << array[i] <<endl;
	}
}
 
 int main () { 
	 int n;
	 cout << "\tDAFTAR NAMA MAHASISWA\t" <<endl;
	 
	 cout << "Masukkan jumlah mahasiswa: ";
	 cin >> n;
	 cin.ignore();
	 
	 string nama [n];
	 
	 cout << "Masukkan Daftar Nama Mashasiswa: " << endl;
	 for (int i = 0; i<n; i++) {
		 cout << "Nama ke-"<< i+1 << ":";
		 getline (cin, nama[i]);
	 }
	 
	 string bubble[n];
	 for (int i=0; i<n; i++) {
		 bubble[i] = nama[i];
	 }
	 bubbleSort(bubble, n);
	 
	 string quick[n];
	 for(int i=0; i<n; i++) {
		 quick[i] = nama[i]; 
	 }
		 
		quickSort(quick, 0, n-1);
		cout << endl;
	 cout << " Daftar nama setelah di-sort (Bubble Sorting):" << endl;
	 tampilData(bubble, n);
	 
	 cout << "Daftar nama setelah di-sort (Quick Sort): " <<endl;
	 tampilData(quick, n);
	 
	 return 0;
	 
	 
		 	 
}
