#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int oncelik;
    time_t zaman;
    char tesis[32];
    char mesaj[1024];
} SyslogGirisi;

typedef struct Dugum {
    SyslogGirisi veri;
    struct Dugum* sonraki;
    struct Dugum* onceki;
} Dugum;

typedef struct {
    Dugum* bas;
    Dugum* son;
    int boyut;
} SyslogListesi;

void listeBaslat(SyslogListesi* liste) {
    liste->bas = NULL;
    liste->son = NULL;
    liste->boyut = 0;
}

Dugum* dugumOlustur(SyslogGirisi giris) {
    Dugum* yeniDugum = (Dugum*)malloc(sizeof(Dugum));
    if (yeniDugum) {
        yeniDugum->veri = giris;
        yeniDugum->sonraki = NULL;
        yeniDugum->onceki = NULL;
    }
    return yeniDugum;
}

void logGirisiEkle(SyslogListesi* liste, SyslogGirisi giris) {
    Dugum* yeniDugum = dugumOlustur(giris);
    if (!yeniDugum) return;

    if (!liste->bas) {
        liste->bas = yeniDugum;
        liste->son = yeniDugum;
    } else {
        yeniDugum->onceki = liste->son;
        liste->son->sonraki = yeniDugum;
        liste->son = yeniDugum;
    }
    liste->boyut++;
}

void tesiseGoreAra(SyslogListesi* liste, const char* tesis) {
    Dugum* simdiki = liste->bas;
    int bulunan = 0;
    
    printf("\n--- %s tesisine ait loglar ---\n", tesis);
    while (simdiki) {
        if (strcmp(simdiki->veri.tesis, tesis) == 0) {
            printf("Zaman: %s", ctime(&simdiki->veri.zaman));
            printf("Mesaj: %s\n", simdiki->veri.mesaj);
            bulunan++;
        }
        simdiki = simdiki->sonraki;
    }
    printf("Toplam %d kayit bulundu.\n", bulunan);
}

void onceligeGoreFiltrele(SyslogListesi* liste, int oncelik) {
    Dugum* simdiki = liste->bas;
    int bulunan = 0;
    
    printf("\n--- oncelik %d olan loglar ---\n", oncelik);
    while (simdiki) {
        if (simdiki->veri.oncelik == oncelik) {
            printf("Tesis: %s\n", simdiki->veri.tesis);
            printf("Mesaj: %s\n", simdiki->veri.mesaj);
            bulunan++;
        }
        simdiki = simdiki->sonraki;
    }
    printf("Toplam %d kayit bulundu.\n", bulunan);
}

void listeyiTemizle(SyslogListesi* liste) {
    Dugum* simdiki = liste->bas;
    while (simdiki) {
        Dugum* sonraki = simdiki->sonraki;
        free(simdiki);
        simdiki = sonraki;
    }
    liste->bas = NULL;
    liste->son = NULL;
    liste->boyut = 0;
}

void ornekKullanim() {
    SyslogListesi liste;
    listeBaslat(&liste);

    SyslogGirisi giris1 = {
        .oncelik = 3,
        .zaman = time(NULL),
        .tesis = "kernel",
        .mesaj = "CPU sicakligi yuksek"
    };

    SyslogGirisi giris2 = {
        .oncelik = 4,
        .zaman = time(NULL),
        .tesis = "auth",
        .mesaj = "Kullanici kimlik dogrulama hatasi"
    };

    logGirisiEkle(&liste, giris1);
    logGirisiEkle(&liste, giris2);

    tesiseGoreAra(&liste, "kernel");
    onceligeGoreFiltrele(&liste, 3);

    listeyiTemizle(&liste);
}

int main() {
    printf("Syslog Analiz Programi Başlatiliyor...\n");
    ornekKullanim();
    printf("\nProgram basariyla tamamlandi.\n");
    return 0;
}