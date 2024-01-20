#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Urun {
    int urunID;
    string urunAdi;
    float urunFiyati;
};

void menuGoster();
void kayitEkle();
void kayitAra();
void kayitDuzelt();
void kayitSil();
void kayitListele();

int main() {
    setlocale(LC_ALL, "Turkish");
    int secim;

    do {
        menuGoster();
        cout << "Seciminizi yapin: ";
        cin >> secim;

        switch (secim) {
        case 1:
            kayitEkle();
            break;
        case 2:
            kayitAra();
            break;
        case 3:
            kayitDuzelt();
            break;
        case 4:
            kayitSil();
            break;
        case 5:
            kayitListele();
            break;
        case 0:
            cout << "Programdan cikiliyor." << endl;
            break;
        default:
            cout << "Geçersiz secim! Tekrar deneyin." << endl;
        }

    } while (secim != 0);

    return 0;
}

void menuGoster() {
    cout << "1. Kayit Ekle" << endl;
    cout << "2. Kayit Ara" << endl;
    cout << "3. Kayit Duzelt/Guncelle" << endl;
    cout << "4. Kayit Sil" << endl;
    cout << "5. Kayitlari Listele" << endl;
    cout << "0. Cikis" << endl;
}

void kayitEkle() {
    ofstream dosya("zuccaciye.dat", ios::app | ios::binary | ios::out);

    if (!dosya) {
        cerr << "Dosya acilamadi." << endl;
        return;
    }

    Urun yeniUrun;

    cout << "Urun ID: ";
    cin >> yeniUrun.urunID;

    cin.ignore();

    cout << "Urun Adi: ";
    getline(cin, yeniUrun.urunAdi);

    cout << "Urun Fiyati: ";
    cin >> yeniUrun.urunFiyati;

    dosya.write(reinterpret_cast<const char*>(&yeniUrun), sizeof(Urun));

    dosya.close();

    cout << "Kayit eklendi." << endl;
}

void kayitAra() {
    ifstream dosya("zuccaciye.dat", ios::binary);

    if (!dosya) {
        cerr << "Dosya acilamadi." << endl;
        return;
    }

    int arananID;
    cout << "Aranacak Urun ID: ";
    cin >> arananID;

    Urun arananUrun;

    bool bulundu = false;

    while (dosya.read(reinterpret_cast<char*>(&arananUrun), sizeof(Urun))) {
        if (arananUrun.urunID == arananID) {
            cout << "Urun ID: " << arananUrun.urunID << endl;
            cout << "Urun Adi: " << arananUrun.urunAdi << endl;
            cout << "Urun Fiyati: " << arananUrun.urunFiyati << endl;

            bulundu = true;
            break;
        }
    }

    if (!bulundu) {
        cout << "Urun bulunamadi." << endl;
    }

    dosya.close();
}

void kayitDuzelt() {
    ifstream dosyaOku("zuccaciye.dat", ios::binary);

    if (!dosyaOku) {
        cerr << "Dosya acilamadi." << endl;
        return;
    }

    ofstream dosyaYaz("temp.dat", ios::binary | ios::out);

    if (!dosyaYaz) {
        cerr << "Temp dosyasi olusturulamadi veya acilamadi." << endl;
        dosyaOku.close();
        return;
    }

    int duzeltilecekID;
    cout << "Duzeltilecek Urun ID: ";
    cin >> duzeltilecekID;

    Urun duzeltilecekUrun;
    bool bulundu = false;

    while (dosyaOku.read(reinterpret_cast<char*>(&duzeltilecekUrun), sizeof(Urun))) {
        if (duzeltilecekUrun.urunID == duzeltilecekID) {
            cout << "Yeni Urun Adi: ";
            cin.ignore();
            getline(cin, duzeltilecekUrun.urunAdi);

            cout << "Yeni Urun Fiyati: ";
            cin >> duzeltilecekUrun.urunFiyati;

            dosyaYaz.write(reinterpret_cast<const char*>(&duzeltilecekUrun), sizeof(Urun));
            bulundu = true;
            cout << "Kayit duzeltildi." << endl;
        }
        else {
            dosyaYaz.write(reinterpret_cast<const char*>(&duzeltilecekUrun), sizeof(Urun));
        }
    }

    if (!bulundu) {
        cout << "Urun bulunamadi." << endl;
    }

    dosyaOku.close();
    dosyaYaz.close();

    remove("zuccaciye.dat");
    rename("temp.dat", "zuccaciye.dat");
}

void kayitSil() {
    ifstream dosyaOku("zuccaciye.dat", ios::binary);

    if (!dosyaOku) {
        cerr << "Dosya acilamadi." << endl;
        return;
    }

    ofstream dosyaYaz("temp.dat", ios::binary | ios::out);

    if (!dosyaYaz) {
        cerr << "Temp dosyasi olusturulamadi veya acilamadi." << endl;
        dosyaOku.close();
        return;
    }

    int silinecekID;
    cout << "Silinecek Urun ID: ";
    cin >> silinecekID;

    Urun silinecekUrun;
    bool bulundu = false;

    while (dosyaOku.read(reinterpret_cast<char*>(&silinecekUrun), sizeof(Urun))) {
        if (silinecekUrun.urunID == silinecekID) {
            cout << "Urun silindi." << endl;
            bulundu = true;
        }
        else {
            dosyaYaz.write(reinterpret_cast<const char*>(&silinecekUrun), sizeof(Urun));
        }
    }

    if (!bulundu) {
        cout << "Urun bulunamadi." << endl;
    }

    dosyaOku.close();
    dosyaYaz.close();

    remove("zuccaciye.dat");
    rename("temp.dat", "zuccaciye.dat");
}

void kayitListele() {
    ifstream dosya("zuccaciye.dat", ios::binary);

    if (!dosya) {
        cerr << "Dosya acilamadi." << endl;
        return;
    }

    Urun urun;

    cout << "************* Kayitli Urunler ************" << endl;

    while (dosya.read(reinterpret_cast<char*>(&urun), sizeof(Urun))) {
        cout << "Urun ID: " << urun.urunID << endl;
        cout << "Urun Adi: " << urun.urunAdi << endl;
        cout << "Urun Fiyati: " << urun.urunFiyati << endl;
        cout << "------------------------" << endl;
    }

    dosya.close();
}
