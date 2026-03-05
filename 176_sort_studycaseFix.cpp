#include <iostream>
using namespace std;

void bubbleSort(string array[], int n){  // fungsi bubble sort untuk mengurutkan data array
	for(int i= 0; i<n-1; i++){ 				// perulangan untuk jumlah sorting
		for(int j=0; j< n-i-1; j++){		// perulangan untuk membandingkan
			if (array[j] > array[j+1]){		// jika array[j] lebih besar dari array selanjutnya
				string temp = array[j]; 	// untuk menukar posisi
				array[j] = array [j+1];		//untuk menukar posisi
				array [j+1]= temp;			// untuk menukar posisi 
				}
			}
		}
 }
 
 int tengah (string array[], int low, int high) { // fungsi untuk menentukan posisi pivot quick sort
	 string pivot = array[high];				//pivot diambil dari data nilai terakhir
	 int i = low - 1;							//indeks nilai yang lebih kecil dari pivot
	 for (int j = low; j< high; j++){			// untuk membandingkan setiap nilai dengan pivot
		 if(array [i]> pivot){					// jika nilai lebih kecil dari pivot 
			 i++;
			 swap (array[i], array[j]);			//menukar nilai array
	 }
 }
 swap (array [i+1], array [high]);				//menempatkan pivot pada posisi yang benar 
 return i+1;									// mengembalikan indeks pivot 
}
 void quickSort(string array[], int low, int high){ //fungsi untuk quick sort 
 if (low< high) {									// jika ada elemen yan perlu diurutkan 
 int ti = tengah(array, low, high); 				// mencari posisi pivot
 quickSort(array, low, ti-1);						// mengurutkan bagian kiri pivot
 quickSort(array, ti+1, high);						// mengurutkan bagian kanan pivot
	}
 }

void tampilData(string array[], int n){			// fungsi untuk menampilkan data mahasiswa 
	for (int i = 0; i<n; i++) {					// perulangan 
	cout << i+1 << "." << array[i] <<endl; 		// menampilkan semua isi array
	}
}
 
 int main () { 
	 int n;
	 cout << "\tDAFTAR NAMA MAHASISWA\t" <<endl; //judul pada tampilan
	 
	 cout << "Masukkan jumlah mahasiswa: "; 	//menampilan perintah user untuk input jumlah data  
	 cin >> n;									// input jumlah
	 cin.ignore();								//membersihkan buffer setelah cin
	 
	 string nama [n];							// array untuk menyimpan nama mahasiswa
	 
	 cout << "Masukkan Daftar Nama Mashasiswa: " << endl; // menampilkan perintah ke user 
	 for (int i = 0; i<n; i++) { 							// perulangan untuk data
		 cout << "Nama ke-"<< i+1 << ":";					// menampilkan data mahasiswa
		 getline (cin, nama[i]);							// untuk membaca nama dengan spasi
	 }
	 
	 string bubble[n];										// string untuk hasil bubble sort
	 for (int i=0; i<n; i++) {								// perulangan untuk menyalin data nama
		 bubble[i] = nama[i];								
	 }
	 bubbleSort(bubble, n);									//memanggil untuk menjalankan bubble sort
	 
	 string quick[n];										// array untuk hasil quick sort
	 for(int i=0; i<n; i++) { 								// perulangan untuk menyalin data dari array nama 
		 quick[i] = nama[i]; 								//sama
	 }
		 
		quickSort(quick, 0, n-1);							//memanggil fungsi quick sort untuk menjalankan
		cout << endl;										//memberi jarak
	 cout << " Daftar nama setelah di-sort (Bubble Sorting):" << endl; //menampilkan daftar nama dari hasil bubble sort
	 tampilData(bubble, n);												// fungsi untuk menampilkan data bubble sort 
	 
	 cout << "Daftar nama setelah di-sort (Quick Sort): " <<endl;		// menampilkan daftar nama dari hasil quick sort 
	 tampilData(quick, n);												// fungsi untuk menampilkan data quick sort 
	 
	 return 0;
	 
	 
		 	 
}
