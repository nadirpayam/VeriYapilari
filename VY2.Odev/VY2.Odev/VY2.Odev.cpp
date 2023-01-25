// VY2.Odev.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


void siraliEkle(struct Yigin* s, int x);
void yiginCikar(struct Yigin* s);
struct Dugum {
    int veri; //düğümün sayısal değeri
    Dugum* sonraki; //sonraki düğüme işaretçi
};

struct Kuyruk {
    Dugum* bas; //kuyruğun başındaki elemanın adresini tutar
    Dugum* son; //kuyruğun sonundaki elemanın adresini tutar
    void olustur(); //başlangıç için gereken tanımları içerir
    void kapat(); //program bitiminde bellek iadesi yapar
    void ekle(int); //kuyruğa yeni veri ekler
    int cikar(); //kuyruktan sıradaki elemanı çıkarır
    bool bosMu(); //kuyruk boş mu kontrol eder
   
};


void Kuyruk::olustur() {
    bas = NULL;
    son = NULL;
}

void Kuyruk::kapat() {
    Dugum* p;
    while (bas) {
        p = bas;
        bas = bas->sonraki;
        delete p;
    }
}

void Kuyruk::ekle(int yeni) {
    Dugum* yenidugum = new Dugum;
    yenidugum->veri = yeni;
    yenidugum->sonraki = NULL;
    if (bas == NULL) {
        bas = yenidugum;
        son = bas;
    }
    else {
        son->sonraki = yenidugum;
        son = yenidugum;
    }
}

int Kuyruk::cikar() {
    Dugum* ustdugum;
    int gecici;
    ustdugum = bas;
    bas = bas->sonraki;
    gecici = ustdugum->veri;
    delete ustdugum;
    return gecici;
}

bool Kuyruk::bosMu() {
    return bas == NULL;
}

struct Yigin {
    Kuyruk k1, k2; //yığın için kullanılacak kuyruk değişkenleri 
    void olustur(); //başlangıç için gereken tanımları içerir
    void kapat(); //program bitiminde bellek iadesi yapar
    void ekle(int); //kuyruğa yeni veri ekler
    int cikar(); //kuyruktan sıradaki elemanı çıkarır
    bool bosMu(); //kuyruk boş mu kontrol eder
    int tepe(); //yığının tepesindeki elemanı okur
    void yazdir(); //yığın elemanlarını sırayla ekrana yazar
};

void Yigin::olustur() {
    k1.olustur();
    k2.olustur();
}

void Yigin::kapat() {
    k1.kapat();
    k2.kapat();
}
void Yigin::ekle(int yeni) {
    k2.ekle(yeni);

    while (!k1.bosMu()) {
        k2.ekle(k1.bas->veri);
        k1.cikar();
    }
    Kuyruk q;
    q = k1;
    k1 = k2;
    k2 = q;
    
}

int Yigin::cikar() {
    if (k1.bosMu())
        return k1.cikar();
   
}

bool Yigin::bosMu() {
    return k1.bosMu();
    return k2.bosMu();
}

void Yigin::yazdir() {
    while (!k1.bosMu()) {
        cout << k1.bas->veri << " ";
        k1.cikar();
    }
}

int Yigin::tepe() {
    if (k1.bosMu())
        return -1;
    return k1.bas->veri;
}


void siraliEkle(struct Yigin* s, int x)
{
    
    if (s->bosMu() ||  s->tepe()) {
        s->ekle(x);
        return;
    }

  
    int tara = s->cikar();
    siraliEkle(s,x);

  
    s->ekle(tara);
}
void yiginCikar(struct Yigin* s)
{

    if (!s->bosMu()) {
 
        int x = s->cikar();

       
        yiginCikar(s);

      
        siraliEkle(s, x);
    }
}
int main()
{
    Yigin x;
    x.olustur();
    x.ekle(3);
    x.ekle(1);
    x.ekle(7);
    x.ekle(4);
    x.ekle(8);
    cout << "Orijinal Yigin:" << endl;
    x.yazdir();

    cout << endl;
    cout << endl;

    cout << "yiginCikar fonksiyon cagrisi" << endl;
    cout << endl;
    yiginCikar(&x);
    siraliEkle(&x, 1);
    siraliEkle(&x, 3);
    siraliEkle(&x, 4);
    siraliEkle(&x, 7);
    siraliEkle(&x, 8);

    cout << "Sirali yigin: " << endl;
    x.yazdir();

}