#include "ojek.hpp"
#include <iostream>
#include <cctype>

using namespace std;

queue<DataOjek> antrianOjek;

// Memasukkan ojek ke antrian paling belakang dan memberi nomor antrian
void KelolaAntrian(DataOjek& ojek) {
    ojek.nomorAntrian = antrianOjek.size() + 1;   // nomor = jumlah ojek di antrian + 1
    antrianOjek.push(ojek);
    cout << "Diberi nomor antrian: " << ojek.nomorAntrian << "\n";
}

// Mengambil ojek paling depan, lalu nomor ojek di belakangnya dikurangi 1
DataOjek PanggilOjek() {
    DataOjek ojek = antrianOjek.front();
    antrianOjek.pop();
    cout << "Ojek dipanggil sesuai nomor antrian: " << ojek.nomorAntrian
         << " (" << ojek.nama << ")\n";

    queue<DataOjek> antrianBaru;
    int nomor = 0;
    while (!antrianOjek.empty()) {
        DataOjek o = antrianOjek.front();
        antrianOjek.pop();
        nomor++;
        o.nomorAntrian = nomor;
        antrianBaru.push(o);
    }
    antrianOjek = antrianBaru;
    return ojek;
}

void LihatAntrian() {
    if (antrianOjek.empty()) {
        cout << "Tidak ada ojek yang aktif dalam antrian.\n";
        return;
    }
    cout << "\n==== Antrian Ojek Saat Ini ====\n";
    queue<DataOjek> salinan = antrianOjek;   // disalin agar antrian asli tidak berubah
    while (!salinan.empty()) {
        cout << salinan.front().nomorAntrian << ". " << salinan.front().nama << "\n";
        salinan.pop();
    }
}

string HurufKecil(string teks) {
    for (size_t i = 0; i < teks.size(); i++) {
        teks[i] = tolower(teks[i]);
    }
    return teks;
}

void CekStatusOjek() {
    DataOjek ojek;
    ojek.statusAktif = false;
    ojek.nomorAntrian = 0;
    cout << "\n==== Aktivasi Layanan Ojek ====\n";

    // Input nama ojek (tidak boleh kosong)
    while (true) {
        cout << "Input nama ojek: ";
        getline(cin, ojek.nama);
        if (ojek.nama != "") break;
        cout << "Nama tidak boleh kosong, silakan isi ulang\n";
    }

    // Konfirmasi status
    string pilihan;
    cout << "\nKonfirmasi status:\n1. Aktif\n2. Tidak aktif\n";
    while (true) {
        cout << "Pilihan: ";
        getline(cin, pilihan);
        if (pilihan == "1" || pilihan == "2") break;
        cout << "Input tidak valid, masukkan 1 atau 2\n";
    }
    ojek.statusAktif = (pilihan == "1");

    // Cek apakah ojek dengan nama ini sudah ada di antrian
    bool sudahAda = false;
    int nomorLama = 0;
    queue<DataOjek> salinan = antrianOjek;
    while (!salinan.empty()) {
        if (HurufKecil(salinan.front().nama) == HurufKecil(ojek.nama)) {
            sudahAda = true;
            nomorLama = salinan.front().nomorAntrian;
        }
        salinan.pop();
    }

    if (ojek.statusAktif) {
        if (sudahAda)
            cout << "Ojek " << ojek.nama << " sudah aktif dengan nomor antrian " << nomorLama << ".\n";
        else
            KelolaAntrian(ojek);
    } else {
        if (sudahAda) {
            // hapus ojek dari antrian, nomor ojek di belakangnya dikurangi 1
            queue<DataOjek> antrianBaru;
            int nomor = 0;
            while (!antrianOjek.empty()) {
                DataOjek o = antrianOjek.front();
                antrianOjek.pop();
                if (HurufKecil(o.nama) != HurufKecil(ojek.nama)) {
                    nomor++;
                    o.nomorAntrian = nomor;
                    antrianBaru.push(o);
                }
            }
            antrianOjek = antrianBaru;
            cout << "Nomor antrian dicabut. Nomor ojek di belakangnya berkurang 1.\n";
        } else {
            cout << "Status tidak aktif. Tidak diberi nomor antrian.\n";
        }
    }
}

void MenuOjek() {
    string pilihan;
    while (true) {
        cout << "\n==== Menu Ojek ====\n1. Aktifkan / nonaktifkan layanan\n2. Lihat antrian sekarang\n3. Keluar\n";
        cout << "Pilihan: ";
        getline(cin, pilihan);

        if (pilihan == "1") {
            CekStatusOjek();
        } else if (pilihan == "2") {
            LihatAntrian();
        } else if (pilihan == "3") {
            cout << "KELUAR DARI MENU OJEK.\n";
            return;
        } else {
            cout << "Input tidak valid, masukkan pilihan yang benar\n";
        }
    }
}