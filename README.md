# 🚀 Mars Kolonisi Yaşam Destek Simülatörü

C dili ile geliştirilmiş, metin tabanlı (CLI) bir hayatta kalma ve kaynak yönetimi oyunudur. Oyuncular, zorlu Mars koşullarında 15 gün boyunca koloni kaynaklarını (Sağlık, Enerji, Oksijen, Su, Yedek Parça) dengede tutarak ve modül hasarını kontrol altında tutarak hayatta kalmaya çalışır.

## 🎮 Oyun Hakkında

Simülasyon toplam **15 gün** sürer ve her **3 geçerli turda 1 gün** ilerler. Gün değişimlerinde koloni atmosferi doğal olarak oksijen tüketir ve modül hasarı kritik seviyedeyse mürettebat sağlığı zarar görür. Amaç, 15. günün sonuna ulaşmak ve en yüksek hayatta kalma puanını toplamaktır.

### ⚙️ Zorluk Seviyeleri

Oyunun başında üç farklı zorluk seviyesinden biri seçilir. Seçilen seviye başlangıç kaynaklarını ve çevresel tehditlerin şiddetini belirler:

| Zorluk Seviyesi | Başlangıç Suyu | Yedek Parça | Başlangıç Hasarı | Fırtına Süresi | Hasar Çarpanı | Keşif Şans Bonusu |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Kolay (`K`)** | 30 | 5 | 10 | 3 Tur | 1x | +10% |
| **Normal (`N`)** | 20 | 3 | 20 | 5 Tur | 1x | 0% |
| **Zor (`Z`)** | 12 | 1 | 35 | 7 Tur | 2x | -10% |

---

## 🕹️ Komutlar ve Oynanış

Her turda aşağıdaki komutlardan birini seçerek koloniyi yönetebilirsiniz:

* **`[G]` Keşif:** Yüzeye çıkarak su (buz tabakası) veya yedek parça (uydu enkazı) ararsınız. Enerji (`-15`) ve oksijen (`-10`) harcar. Kaza geçirme riski vardır.
* **`[O]` Oksijen Üretimi:** Depodaki suyu işleyerek oksijene dönüştürürsünüz. Her `2` birim su, `3` birim oksijen üretir (`-10` Enerji).
* **`[T]` Tamir:** Yedek parça ve enerji (`-10`) kullanarak modül hasarını onarırsınız. Hasar seviyesine göre (Hafif, Orta, Ağır) gereken yedek parça miktarı artar.
* **`[D]` Durum Raporu:** Tur harcamadan koloninin detaylı istatistiklerini ve kritik sistem uyarılarını görüntülersiniz.
* **`[U]` Uyu (Dinlen):** Enerji (`+25`) ve sağlık (`+15`) yeniler, ancak oksijen (`-8`) tüketir. Oksijen seviyesi 20'nin altındaysa sağlık kaybı yaşanır.
* **`[K]` Kum Fırtınası:** Fırtına simülasyonunu tetikler (`-10` Enerji). Zorluk seviyesine bağlı tur boyunca oksijen sızıntısı, modül hasarı veya yaralanma riskleri oluşur. Hava kilidinin mühürlü olması oksijen sızıntısını engeller.
* **`[H]` Hava Kilidi:** Kum fırtınalarından korunmak için hava kilidini mühürlemeye yarayan mini şifre çözme oyunudur. O günün sayısına göre Sezar şifrelemesi mantığıyla (`'A' + gün`) harf tahmini yapılır.
* **`[Q]` Çıkış:** Simülasyonu sonlandırır ve sonuç raporunu gösterir.

---

## 🏆 Puanlama Sistemi

Oyun tamamlandığında veya kaybedildiğinde performansınız şu formülle hesaplanır:

$$\text{Toplam Puan} = (\text{Gün} \times 100) + \text{Sağlık} + \text{Oksijen} - \text{Modül Hasarı}$$

---

