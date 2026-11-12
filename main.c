//
//  main.c
//  MyTool
//
//  Created by ECREN on 12.11.2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)(time(NULL)));
    int saglik = 100, enerji = 100, oksijen = 100, su = 0, yedekParca = 0, modulHasari = 0;
    int kilitMuhurlu = 0, gun = 1, tur = 0, oyunBitti = 0, gecerliZorluk = 0;
    int firtinaTuru = 5, hasarCarpani = 1, kesifEsikBonus = 0;
    int esik, zar, bulunanSu, bulunanParca, kazaZari, kayip, turGecerli;
    int harcanacakSu, artikSu, islenenSu, uretilenOksijen;
    int hasarAlinanTur, topSaglikKaybi, topOksijenKaybi, i, siddetCarpani, firtinaZari, olayTipi, kayipO2, ekHasar, kayipCan;
    int deneme, maksDeneme, puan;
    char zorluk, komut, hedefSifre, tahmin;

    printf("=== MARS KOLONISI YASAM DESTEK SIMULATORU (15 GUN) ===\n");

    do {
        printf("Zorluk Seviyesi Secin (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);
        switch (zorluk) {
            case 'k':
            case 'K':
                su = 30; yedekParca = 5; modulHasari = 10;
                firtinaTuru = 3; hasarCarpani = 1; kesifEsikBonus = 10;
                gecerliZorluk = 1;
                printf("[BILGI] Kolay mod secildi.\n");
                break;
            case 'n':
            case 'N':
                su = 20; yedekParca = 3; modulHasari = 20;
                firtinaTuru = 5; hasarCarpani = 1; kesifEsikBonus = 0;
                gecerliZorluk = 1;
                printf("[BILGI] Normal mod secildi.\n");
                break;
            case 'z':
            case 'Z':
                su = 12; yedekParca = 1; modulHasari = 35;
                firtinaTuru = 7; hasarCarpani = 2; kesifEsikBonus = -10;
                gecerliZorluk = 1;
                printf("[BILGI] Zor mod secildi.\n");
                break;
            default:
                printf("[UYARI] Gecersiz zorluk seviyesi! Lutfen K, N veya Z girin.\n");
                break;
        }
    } while (!gecerliZorluk);

    do {
        turGecerli = 0;
        printf("\n--------------------------------------------------\n");
        printf("GUN: %d/15 | TUR: %d | Saglik: %d | Enerji: %d | Oksijen: %d\n", gun, tur, saglik, enerji, oksijen);
        printf("Su: %d | Parca: %d | Hasar: %d | Kilit: %s\n", su, yedekParca, modulHasari, kilitMuhurlu ? "MUHURLU" : "ACIK");
        printf("Komutlar: [G]esif [O]ksijen [T]amir [D]urum [U]yu [K]um Firtinasi [H]ava Kilidi [Q]Cikis\n");
        printf("Komutunuz: ");
        scanf(" %c", &komut);

        switch (komut) {
            case 'g':
            case 'G':
                if (enerji < 15) {
                    printf("[IPTAL] Yetersiz enerji! (Gereken: 15, Mevcut: %d)\n", enerji);
                    break;
                }
                enerji -= 15; oksijen -= 10; turGecerli = 1;
                esik = ((enerji > 40 && oksijen > 30) ? 65 : 40) + kesifEsikBonus;
                if (esik < 15) esik = 15;
                if (esik > 90) esik = 90;
                zar = rand() % 100;
                printf("Kesif Zari: %d / Esik: %d -> %s\n", zar, esik, (zar < esik) ? "BASARILI" : "BASARISIZ");
                if (zar < esik / 2) {
                    bulunanSu = 6 + (rand() % 6); su += bulunanSu;
                    printf("[SONUC] Buz tabakasi bulundu! +%d Su.\n", bulunanSu);
                } else if (zar < esik) {
                    bulunanParca = 1 + (rand() % 2); yedekParca += bulunanParca;
                    printf("[SONUC] Uydu enkazi bulundu! +%d Yedek Parca.\n", bulunanParca);
                } else {
                    printf("[SONUC] Kaynak bulunamadi, eli bos dondunuz.\n");
                }
                kazaZari = rand() % 100;
                printf("Guvenlik Zari: %d / Esik: 10 (veya Hasar > 70) -> %s\n", kazaZari, (kazaZari < 10 || modulHasari > 70) ? "YARALANMA" : "GUVENLI");
                if (kazaZari < 10 || modulHasari > 70) {
                    kayip = 12 * hasarCarpani; saglik -= kayip;
                    printf("[TEHLIKE] Kesifte yaralandiniz! -%d Saglik.\n", kayip);
                }
                break;
            
            case 'o':
            case 'O':
                if (enerji < 10 || su < 2) {
                    printf("[IPTAL] Yetersiz kaynak (Enerji >= 10, Su >= 2 olmali)!\n");
                    break;
                }
                printf("Kullanilacak su miktarini girin (Mevcut: %d): ", su);
                scanf("%d", &harcanacakSu);
                if (harcanacakSu < 2 || harcanacakSu > su) {
                    printf("[IPTAL] Gecersiz miktar!\n");
                    break;
                }
                artikSu = harcanacakSu % 2;
                islenenSu = harcanacakSu - artikSu;
                uretilenOksijen = (islenenSu / 2) * 3;
                su -= islenenSu; enerji -= 10; oksijen += uretilenOksijen; turGecerli = 1;
                if (artikSu == 1) printf("[BILGI] 1 birim su artik olarak depoda kaldi.\n");
                printf("[SONUC] %d su islendi, +%d oksijen uretildi.\n", islenenSu, uretilenOksijen);
                break;

            case 't':
            case 'T':
                if (enerji < 10 || yedekParca <= 0 || modulHasari == 0) {
                    printf("[IPTAL] Tamir kosullari saglanmiyor!\n");
                    break;
                }
                if (modulHasari <= 30) {
                    yedekParca -= 1; enerji -= 10; modulHasari -= 15; turGecerli = 1;
                    printf("[TAMIR - HAFIF] 1 parca harcandi, 15 hasar onarildi.\n");
                } else if (modulHasari <= 70) {
                    if (yedekParca < 2) { printf("[IPTAL] 2 yedek parca gerekiyor!\n"); break; }
                    yedekParca -= 2; enerji -= 10; modulHasari -= 30; turGecerli = 1;
                    printf("[TAMIR - ORTA] 2 parca harcandi, 30 hasar onarildi.\n");
                } else {
                    if (yedekParca < 3) { printf("[IPTAL] 3 yedek parca gerekiyor!\n"); break; }
                    yedekParca -= 3; enerji -= 10; modulHasari -= 45; turGecerli = 1;
                    printf("[TAMIR - AGIR] 3 parca harcandi, 45 hasar onarildi.\n");
                }
                break;

            case 'd':
            case 'D':
                printf("\n=== DETAYLI DURUM RAPORU ===\n");
                printf("Gun: %d/15 | Tur: %d | Saglik: %d | Enerji: %d | Oksijen: %d\n", gun, tur, saglik, enerji, oksijen);
                printf("Su: %d | Parca: %d | Hasar: %d | Kilit: %s\n", su, yedekParca, modulHasari, kilitMuhurlu ? "Muhurlu" : "Acik");
                if (oksijen < 25) printf("[KRITIK UYARI] Oksijen kritik seviyede dusuk!\n");
                if (saglik < 30) printf("[KRITIK UYARI] Saglik tehlikede!\n");
                if (enerji < 20) printf("[KRITIK UYARI] Enerji cok dusuk!\n");
                if (modulHasari > 70) printf("[KRITIK UYARI] Modul hasari kritik seviyede!\n");
                if (oksijen >= 25 && saglik >= 30 && enerji >= 20 && modulHasari <= 70) printf(">>> TUM SISTEMLER NORMAL <<<\n");
                break;

            case 'u':
            case 'U':
                enerji += 25; oksijen -= 8; turGecerli = 1;
                if (oksijen < 20) {
                    saglik -= 10;
                    printf("[TEHLIKE] Oksijen 20 altinda! Saglik artmadi, -10 Saglik.\n");
                } else {
                    saglik += 15;
                    printf("[DINLENME] +25 Enerji, +15 Saglik, -8 Oksijen.\n");
                }
                break;
            
            case 'k':
            case 'K':
                if (enerji < 10) { printf("[IPTAL] Yetersiz enerji!\n"); break; }
                enerji -= 10; turGecerli = 1;
                hasarAlinanTur = 0; topSaglikKaybi = 0; topOksijenKaybi = 0;
                printf("\n[ALARM] Kum Firtinasi Basladi! (%d Tur)\n", firtinaTuru);
                for (i = 1; i <= firtinaTuru; i++) {
                    siddetCarpani = (i % 2 == 0) ? 2 : 1;
                    firtinaZari = rand() % 100; esik = 65;
                    printf("  Tur %d | Zar: %d / Esik: %d -> ", i, firtinaZari, esik);
                    if (firtinaZari >= esik) { printf("KORUNMA\n"); continue; }
                    olayTipi = firtinaZari % 3;
                    if (olayTipi == 0) {
                        if (kilitMuhurlu == 1) { printf("SIZINTI ENGELLENDI\n"); continue; }
                        kayipO2 = 6 * siddetCarpani * hasarCarpani;
                        oksijen -= kayipO2; topOksijenKaybi += kayipO2; hasarAlinanTur++;
                        printf("OKSIJEN SIZINTISI (-%d Oksijen)\n", kayipO2);
                    } else if (olayTipi == 1) {
                        ekHasar = 8 * siddetCarpani * hasarCarpani;
                        modulHasari += ekHasar; hasarAlinanTur++;
                        printf("MODUL HASARI (+%d Hasar)\n", ekHasar);
                    } else {
                        kayipCan = 7 * siddetCarpani * hasarCarpani;
                        saglik -= kayipCan; topSaglikKaybi += kayipCan; hasarAlinanTur++;
                        printf("YARALANMA (-%d Saglik)\n", kayipCan);
                    }
                    if (saglik <= 0 || oksijen <= 0) {
                        if (saglik < 0) saglik = 0;
                        if (oksijen < 0) oksijen = 0;
                        printf("  [KRITIK] Yasam degerleri tukendi!\n"); break;
                    }
                }
                printf("--- OZET: Hasar Alinan Tur: %d | Saglik Kaybi: %d | Oksijen Kaybi: %d ---\n", hasarAlinanTur, topSaglikKaybi, topOksijenKaybi);
                break;

            case 'h':
            case 'H':
                if (kilitMuhurlu == 1 || enerji < 5) { printf("[IPTAL] Kilit muhurlu veya enerji yetersiz!\n"); break; }
                hedefSifre = 'A' + (gun % 26); deneme = 0; maksDeneme = 3;
                printf("IPUCU: Sifre 'A' harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n", gun);
                do {
                    printf("Sifre Tahmini (%d/%d): ", deneme + 1, maksDeneme);
                    scanf(" %c", &tahmin);
                    if (tahmin >= 'a' && tahmin <= 'z') tahmin = tahmin - ('a' - 'A');
                    deneme++;
                    if (tahmin == hedefSifre) {
                        kilitMuhurlu = 1; printf("[BASARILI] Hava kilidi muhurlendi!\n");
                    } else {
                        enerji -= 5; if (enerji < 0) enerji = 0;
                        printf("[HATALI] -5 Enerji. Ipucu: %s\n", (tahmin < hedefSifre) ? "ILERI git" : "GERI git");
                    }
                } while (tahmin != hedefSifre && deneme < maksDeneme);
                if (kilitMuhurlu == 0) { modulHasari += 20; printf("[ALARM] Hak doldu! +20 Modul Hasari.\n"); }
                turGecerli = 1;
                break;

            case 'q':
            case 'Q':
                printf("[CIKIS] Simulasyon sonlandirildi.\n"); oyunBitti = 1;
                break;

            default:
                printf("[UYARI] Tanimsiz komut!\n");
                break;
        }

        if (saglik < 0) saglik = 0; if (saglik > 100) saglik = 100;
        if (enerji < 0) enerji = 0; if (enerji > 100) enerji = 100;
        if (oksijen < 0) oksijen = 0; if (oksijen > 100) oksijen = 100;
        if (modulHasari < 0) modulHasari = 0; if (modulHasari > 100) modulHasari = 100;

        if (turGecerli == 1 && !oyunBitti) {
            tur++;
            if (tur % 3 == 0) {
                gun++; oksijen -= 8;
                printf("\n>>> YENI GUN BASLADI (Gun %d) | -8 Oksijen <<<\n", gun);
                if (modulHasari > 70) { saglik -= 5; printf("[KRITIK HASAR] -5 Saglik!\n"); }
                if (oksijen < 0) oksijen = 0; if (saglik < 0) saglik = 0;
            }
        }

        if (!oyunBitti) {
            if (saglik <= 0 || oksijen <= 0) {
                printf("\n=== OYUN KAYBEDILDI! ===\n"); oyunBitti = 1;
            } else if (gun > 15) {
                gun = 15; printf("\n=== TEBRIKLER! 15. GUNU TAMAMLADINIZ! ===\n"); oyunBitti = 1;
            }
        }
    } while (!oyunBitti);

    puan = (gun * 100) + saglik + oksijen - modulHasari;
    if (puan < 0) puan = 0;
    printf("\n=== SONUC RAPORU ===\n");
    printf("Gun: %d | Tur: %d | Saglik: %d | Enerji: %d | Oksijen: %d | Su: %d | Parca: %d | Hasar: %d\n", gun, tur, saglik, enerji, oksijen, su, yedekParca, modulHasari);
    printf("TOPLAM PUAN: %d\n", puan);
    return 0;
}
