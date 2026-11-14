#include "tarif.hpp"
#include "ojek.hpp"
#include <iostream>
#include <cmath>

using namespace std;

void PilihTujuan(DataRute& rute, string& nama) {
    cout << "\n==== Data Perjalanan ====\n";

    // Tujuan dan nama tidak boleh kosong
    while (true) {
        cout << "Tujuan: ";
        getline(cin, rute.namaTujuan);
        cout << "Nama penumpang: ";
        getline(cin, nama);
        if (rute.namaTujuan != "" && nama != "") break;
        cout << "Tujuan dan nama tidak boleh kosong\n";
    }

    // Jarak harus angka lebih dari 0 (maksimal 500 km)
    while (true) {
        cout << "Jarak perjalanan (km): ";
        cin >> rute.jarak;
        // cin.fail() = yang diketik bukan angka, cin.peek() != '\n' = ada karakter lain setelah angka
        bool valid = !cin.fail() && cin.peek() == '\n' && rute.jarak > 0 && rute.jarak <= 500;
        cin.clear();
        cin.ignore(1000, '\n');   // buang sisa baris agar getline berikutnya normal
        if (valid) break;
        cout << "Jarak tidak valid, masukkan angka lebih dari 0 (maks 500 km)\n";
    }
}

bool KonfirmasiPersetujuan() {
    string pilihan;
    cout << "\nSetuju dengan tarif?\n1. Setuju\n2. Tidak setuju\n";
    while (true) {
        cout << "Pilihan: ";
        getline(cin, pilihan);
        if (pilihan == "1") return true;
        if (pilihan == "2") return false;
        cout << "Input tidak valid.\n";
    }
}

void MenuMahasiswa() {
    // Apakah ada ojek yang aktif?
    if (antrianOjek.empty()) {
        cout << "Layanan tidak tersedia (tidak ada ojek aktif).\n";
        return;
    }

    string pilihan;
    while (true) {
        cout << "\n==== Menu Mahasiswa ====\n1. Masukkan tujuan dan nama penumpang\n2. Keluar\n";
        cout << "Pilihan: ";
        getline(cin, pilihan);

        if (pilihan == "2") {
            cout << "KELUAR DARI MENU MAHASISWA\n";
            return;
        }
        if (pilihan != "1") {
            cout << "Input tidak valid, masukkan pilihan yang benar\n";
            continue;
        }

        DataRute rute;
        string nama;
        PilihTujuan(rute, nama);

        // Tarif = jarak x Rp 5.000
        rute.hargaTarif = round(rute.jarak * TARIF_PER_KM);
        cout << "\n==== Rincian Tarif ====\n"
             << "Tujuan : " << rute.namaTujuan << "\n"
             << "Jarak  : " << rute.jarak << " km\n"
             << "Tarif  : " << rute.jarak << " km x Rp " << TARIF_PER_KM
             << " = Rp " << rute.hargaTarif
             << " (harga pasti, tanpa tawar-menawar)\n";

        if (KonfirmasiPersetujuan()) {
            DataOjek ojek = PanggilOjek();
            cout << "Menuju lokasi " << rute.namaTujuan << "...\n";
            cout << "Melakukan pembayaran Rp " << rute.hargaTarif
                 << " oleh " << nama << ". Terima kasih!\n";
            cout << "Ojek " << ojek.nama << " selesai mengantar dan kembali ke antrian.\n";
            KelolaAntrian(ojek);   // ojek masuk lagi di antrian paling belakang
            return;
        }

        string ubah;
        cout << "\nApakah ingin merubah tujuan?\n1. Ya\n2. Tidak\n";
        while (true) {
            cout << "Pilihan: ";
            getline(cin, ubah);
            if (ubah == "1" || ubah == "2") break;
            cout << "Input tidak valid.\n";
        }
        if (ubah == "1") continue;   // kembali ke menu mahasiswa
        cout << "Keluar dari sistem.\n";
        return;
    }
}