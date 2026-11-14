#include <iostream>
#include "ojek.hpp"
#include "tarif.hpp"

using namespace std;

int main() {
    cout << "=== Sistem Digitalisasi Pangkalan Ojek & Transparansi Tarif ===\n";

    string pilihan;
    while (true) {
        cout << "\n==== MENU UTAMA ====\n1. Ojek\n2. Mahasiswa\n0. Keluar program\n";
        cout << "Pilih Role: ";
        getline(cin, pilihan);

        if (pilihan == "1") {
            MenuOjek();
        } else if (pilihan == "2") {
            MenuMahasiswa();
        } else if (pilihan == "0") {
            cout << "Terima kasih.\n";
            return 0;
        } else {
            cout << "Input tidak valid\n";
        }
    }
}