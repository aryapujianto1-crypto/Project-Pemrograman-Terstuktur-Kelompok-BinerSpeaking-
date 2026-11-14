#ifndef OJEK_HPP
#define OJEK_HPP

#include <string>
#include <queue>
using namespace std;

struct DataOjek {
    string nama;
    bool statusAktif;
    int nomorAntrian;
};

// antrian ojek aktif (yang masuk lebih dulu, dipanggil lebih dulu)
extern queue<DataOjek> antrianOjek;

void CekStatusOjek();               // input nama + konfirmasi status
void KelolaAntrian(DataOjek& ojek); // masukkan ojek ke antrian paling belakang + beri nomor
DataOjek PanggilOjek();             // ambil ojek paling depan dari antrian
void LihatAntrian();                // tampilkan seluruh antrian
void MenuOjek();

#endif