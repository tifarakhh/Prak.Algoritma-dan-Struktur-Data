#include <iostream>
using namespace std;

int main () {
	
	int bebas[5] = {30, 29, 27, 20, 16}; // array interger dengan panjang 5 
	int t = 5; 							// jumlah index
	int *ptr = bebas; // pointer menunjuk ke alamat 
	
	cout << " Nilai Array: ";  // menunjukkan nilai array yang akan dihitung
	for (int i=0; i<t; i++) { // perulangan
		cout << *(ptr + i) << ", "; // menampilkan menggunakan pointer 
	}
	
	int maks = *ptr; 			 // inisialisasi maksimum
	int min = *ptr; 			// inisialisasi minimum
	for (int i=0; i<t; i++) {  // perulangan 
		if (*(ptr + i) > maks ) { // jika nilai lebih besar
			maks = *(ptr + i); 	 // perolehan nilai maksimum
		}
		if (*(ptr + i) < min) { // jika nilai lebih kecil
			min = *(ptr + i);  // perolehan nilai minimum 
		}
	}
	
	int jumlah = 0; // inisialisasi jumlah 
		for (int i = 0; i<t; i++) {  //perulangan 
			jumlah += *(ptr + i);  // menjumlahkan 
		}
		int rerata = jumlah / t; // rata-rata nilai
		
		cout << endl; //memberi jarak
		cout << "Nilai maksimum: " << maks << endl; //output nilai mkasimum 
		cout << "Nilai minimum: " <<min << endl; // output nilai minimum
		cout << "Jumlah: " <<jumlah << endl; 	// output jumlah
		cout << "Rata-rata: " << rerata << endl; // output rata-rata 
	
	
	
}
