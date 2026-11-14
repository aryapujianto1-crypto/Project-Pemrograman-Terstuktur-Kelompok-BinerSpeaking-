#ifndef TARIF_HPP
#define TARIF_HPP

#include <string>
using namespace std;

const int TARIF_PER_KM = 5000;   // 1 km = Rp 5.000

struct DataRute {
    string namaTujuan;
    double jarak;     // km (diinput mahasiswa)
    int hargaTarif;   // rupiah
};

void PilihTujuan(DataRute& rute, string& nama);  // input tujuan, nama, dan jarak
bool KonfirmasiPersetujuan();                          // true = setuju, false = tidak setuju
void MenuMahasiswa();

#endif