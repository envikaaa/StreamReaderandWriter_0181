#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class TokoElektronik
{
private:
    array<string, 3> etalase; // enkapsulasi

public:
    // Constructor
    TokoElektronik()
    {
        etalase[0] = "Laptop";
        etalase[1] = "Smartphone";
        etalase[2] = "Printer";
    }

    // Method mengambil produk
    string ambilProduk(size_t nomorRak)
    {
        try
        {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&)
        {
            throw string(
                "Gagal Mengambil Barang : Rak nomor " +
                to_string(nomorRak) +
                " kosong atau tidak tersedia!");
        }
    }
};

void tampilkanData()
{
    ifstream file("gudang.txt");
    string data;

    cout << "\n===== DATA GUDANG =====\n";

    int nomor = 1;
    bool kosong = true;

    while (getline(file, data))
    {
        cout << nomor++ << ". " << data << endl;
        kosong = false;
    }

    if (kosong)
    {
        cout << "Data gudang masih kosong.\n";
    }

    file.close();
}

void tambahBarang()
{
    ofstream file("gudang.txt", ios::app);

    string barang;

    cin.ignore();
    cout << "Masukkan nama barang : ";
    getline(cin, barang);

    file << barang << endl;
    file.close();
    cout << "Barang berhasil ditambahkan!\n";
}

void updateBarang()
{
    ifstream file("gudang.txt");

    vector<string> data;
    string barang;

    while (getline(file, barang))
    {
        data.push_back(barang);
    }

    file.close();

    if (data.empty())
    {
        cout << "Data kosong!\n";
        return;
    }

    tampilkanData();

    int nomor;
    cout << "\nPilih nomor barang yang ingin diubah : ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size())
    {
        cout << "Nomor tidak valid!\n";
        return;
    }

    cin.ignore();
    cout << "Masukkan nama barang baru : ";
    getline(cin, barang);

    data[nomor - 1] = barang;

    ofstream out("gudang.txt");

    for (string item : data)
    {
        out << item << endl;
    }

    out.close();
    cout << "Data berhasil diperbarui!\n";
}

void hapusBarang()
{
    ifstream file("gudang.txt");

    vector<string> data;
    string barang;

    while (getline(file, barang))
    {
        data.push_back(barang);
    }

    file.close();

    if (data.empty())
    {
        cout << "Data kosong!\n";
        return;
    }

    tampilkanData();

    int nomor;
    cout << "\nPilih nomor barang yang ingin dihapus : ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size())
    {
        cout << "Nomor tidak valid!\n";
        return;
    }
    data.erase(data.begin() + nomor - 1);
    ofstream out("gudang.txt");
    for (string item : data)
    {
        out << item << endl;
    }

    out.close();
    cout << "Data berhasil dihapus!\n";
}

void simulasiEtalase()
{
    TokoElektronik toko;

    cout << "\n===== SIMULASI ETALASE =====\n";

    try
    {
        cout << "\nSkenario 1 (Rak 1)\n";
        cout << "Barang : "
             << toko.ambilProduk(1)
             << endl;
    }
    catch (string pesan)
    {
        cout << pesan << endl;
    }

    try
    {
        cout << "\nSkenario 2 (Rak 5)\n";
        cout << "Barang : "
             << toko.ambilProduk(5)
             << endl;
    }
    catch (string pesan)
    {
        cout << pesan << endl;
    }
}

int main()
{
    int pilihan;
    do
    {
        cout << "\n==================================";
        cout << "\n   TOKO ELEKTRONIK GIBRAN JAYA";
        cout << "\n==================================";

        tampilkanData();

        cout << "\nMENU UTAMA";
        cout << "\n1. Tambah Barang (Create)";
        cout << "\n2. Lihat Barang (Read)";
        cout << "\n3. Update Barang";
        cout << "\n4. Hapus Barang (Delete)";
        cout << "\n5. Simulasi Etalase";
        cout << "\n0. Keluar";
        cout << "\nPilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahBarang();
            break;

        case 2:
            tampilkanData();
            break;

        case 3:
            updateBarang();
            break;

        case 4:
            hapusBarang();
            break;

        case 5:
            simulasiEtalase();
            break;

        case 0:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak tersedia!\n";
        }

    } while (pilihan != 0);

    return 0;
}