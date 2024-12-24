//Kütüphaneler
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include "TouchScreen.h"
#include <stdint.h>



MCUFRIEND_kbv tft(A3, A2, A1, A0, A4);
TouchScreen ts = TouchScreen(9, A2, A3, 8, 300);

//Uygulamada kullanılar kelimeler
String A1_ingilizce[] = { "Know", "Think", "Action", "Bring", "Catch", "Run", "Drink",
                          "Swim", "Break", "Forget", "Wear", "Fall", "Eat", "Take", "Lose",
                          "Try", "Hear", "Sit", "Alone", "Angry" };

String A1_turkce[] = { "Bilmek", "Dusunmek", "Hareket", "Getirmek", "Yakalamak",
                       "Kosmak", "Icmek", "Yuzmek", "Kirmak", "Unutmak", "Giymek",
                       "Dusmek", "Yemek", "Almak", "Kaybetmek", "Denemek", "Duymak",
                       "Oturmak", "Yalniz", "Kizgin" };

String A2_ingilizce[] = { "Accept", "Accident", "Adventure", "Agree", "Begin", "Believe",
                          "Bite", "Brain", "Busy", "Cash", "Choose", "Climb", "Cut", "Cute",
                          "Dangerous", "Delete", "Die", "Expensive", "Explain", "Fill" };

String A2_turkce[] = { "Kabul etmek", "Kaza", "Macera", "Anlasmak", "Baslamak", "Inanmak",
                       "Isirmak", "Beyin", "Mesgul", "Nakit", "Secmek", "Tirmanmak", "Kesmek",
                       "Sevimli", "Tehlikeli", "Silmek", "Olmek", "Pahali", "Aciklamak", "Doldurmak" };

String B1_ingilizce[] = { "Advice", "Art", "Attack", "Blood", "Destroy", "Engine", "Import", "Low",
                          "Peace", "Poison", "Population", "Publish", "Remove", "Result", "Search",
                          "Space", "Tool", "Trade", "Truck", "Wide" };

String B1_turkce[] = { "Tavsiye", "Sanat", "Saldiri", "Kan", "Yikmak", "Motor", "Ithalat", "Dusuk",
                       "Baris", "Zehir", "Populasyon", "Yayinlamak", "Kaldirmak", "Sonuc", "Arastirmak",
                       "Bosluk", "Alet", "Ticaret", "Kamyon", "Genis" };

String yanlis_ingilizce[20] = { "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos" };
String yanlis_turkce[20] = { "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos", "bos" };
short yanlis_sayac = 0;
bool kontrol1 = false;
short yanlis_eleman = 0;
bool hata_soru = false;


//uygulamadaki değişkenler
short sayfa;   //sayfa değişkeni 1(giriş),2(seviye seçimi)ve 3(soru cevap sayfası) olarak kullanıldı
short seviye;  // seviye değişkeni 1(A1),2(A2)ve 3(B1) olarak kullanıldı
short skor;    // soru bildikçe 1 arttırıldı yanlış cevapta sıfırlandı
// Şıklarda kullanılan kelimelerin dizi sırası için kullanıldı
short Dsayi;
short Ysayi;
short Y1sayi;

short yer;            // Doğru kelimenin  hangi şıkta olacağını belirlemek için kullanıldı 1(a),2(b) ve 3(c).
short cevap_bekleme;  //Soru cevap sayfası yüklendikten sonra cevap verilene kadar sayfanın değişmemesi için kullanılı
short onceki_kelime;  // Peşpeşe aynı ingilizce kelime gelmemesi için kullanıldı


void setup() {
  // Ekran ve arduino kart bağlantıları
  tft.reset();
  uint8_t ID = tft.readID();
  tft.begin(ID);
  Serial.begin(9600);


  sayfa = 1;
  skor = 0;
  cevap_bekleme = 0;

  //Giriş sayfası
  tft.setRotation(3);
  tft.fillScreen(0x0000);
  tft.setCursor(40, 40);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(4);
  tft.print("ingilizce kelime");

  tft.setCursor(170, 90);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(4);
  tft.print("oyunu");

  tft.drawRect(140, 205, 150, 60, 0xFFFF);
  tft.setCursor(160, 220);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(4);
  tft.print("Basla");
}

void loop() {


  TSPoint p = ts.getPoint();  //Ekranda dokunulan kısımdaki pixelin x ve y kordinatını almak için

  if (p.z > ts.pressureThreshhold) {  //Ekrana baskı kuvveti belirli bi orandan sonra ekranın algılaması için
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);



    delay(100);


    //Giriş sayfasından seviye seçim sayfasına geçiş
    if (p.x > 660 && p.x < 805 && p.y > 372 && p.y < 639 && sayfa == 1) {
      sayfa = 2;
      tft.fillScreen(0x0000);
      tft.setCursor(60, 100);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("Seviye Seciniz");

      tft.setCursor(80, 200);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("A1");

      tft.setCursor(190, 200);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("A2");

      tft.setCursor(310, 200);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("B1");

      tft.fillRect(0, 20, 78, 40, 0xFFFF);
      tft.setCursor(5, 30);
      tft.setTextColor(0x0000);
      tft.setTextSize(3);
      tft.print("Geri");
      p.x = 0;
      p.y = 0;
    }
    Serial.println(p.x);
    Serial.println(p.y);
    delay(100);

    //Seviye seçme sayfasında yani sayfa 2 de basılan pixelin kordinatına göre seviye seçimi
    if (sayfa == 2) {
      if (p.x > 650 && p.x < 741 && p.y > 290 && p.y < 374) {  //A1 seviyesi
        sayfa = 3;
        seviye = 1;
        cevap_bekleme = 0;
        p.x = 0;
        p.y = 0;
      }

      else if (p.x > 657 && p.x < 736 && p.y > 475 && p.y < 569) {  //A2 seviyesi
        sayfa = 3;
        seviye = 2;
        cevap_bekleme = 0;
        p.x = 0;
        p.y = 0;
      }

      else if (p.x > 657 && p.x < 728 && p.y > 679 && p.y < 752) {  //B1 seviyesi

        sayfa = 3;
        seviye = 3;
        cevap_bekleme = 0;

        p.x = 0;
        p.y = 0;
      }
    }
    delay(100);
    // Soru cevap sayafasıdaki yani sayfa 3 teki geri butonuna basınca sayfa 2 yi açması için
    if (p.x < 340 && p.x > 170 && p.y < 310 && p.y > 163 && sayfa == 3) {
      sayfa = 2;
      tft.fillScreen(0x0000);
      tft.setCursor(60, 100);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("Seviye Seciniz");

      tft.setCursor(80, 200);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("A1");

      tft.setCursor(190, 200);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("A2");

      tft.setCursor(310, 200);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("B1");

      tft.fillRect(0, 20, 78, 40, 0xFFFF);
      tft.setCursor(5, 30);
      tft.setTextColor(0x0000);
      tft.setTextSize(3);
      tft.print("Geri");

      for (int i = 0; i < 20; i++) {
        yanlis_ingilizce[i] = "bos";
        yanlis_turkce[i] = "bos";
        yanlis_eleman = 0;
        yanlis_sayac = 0;
      }


      cevap_bekleme = 0;
      skor = 0;
      p.x = 0;
      p.y = 0;
    }
    //Seviye seçme sayfasındaki geri butonuna basınca sayfa 1 i açar
    if (p.x < 340 && p.x > 170 && p.y < 310 && p.y > 163 && sayfa == 2) {
      sayfa = 1;

      tft.fillRect(0, 20, 78, 40, 0xFFFF);
      tft.setCursor(5, 30);
      tft.setTextColor(0x0000);
      tft.setTextSize(3);
      tft.print("Geri");

      tft.setRotation(3);
      tft.fillScreen(0x0000);
      tft.setCursor(40, 40);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("ingilizce kelime");

      tft.setCursor(170, 90);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("oyunu");

      tft.drawRect(140, 205, 150, 60, 0xFFFF);
      tft.setCursor(160, 220);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(4);
      tft.print("Basla");

      cevap_bekleme = 0;
      skor = 0;
      p.x = 0;
      p.y = 0;
    } 

    /* Cevaba dokunduktan sonra pixel kordinatına göre doğru yanlış kontrolü için 
    not:cevap kontrolü soru kodlarında önce yazılmıştır çünkü soru kodlarından sonra yazıldığı zaman cevaba 2 defa tıklandıktan sonra diğer soru sayfası açılıyordu.*/
    if (yer == 1 && p.x < 709 && p.x > 646 && p.y < 372 && p.y > 189 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 1. şıkta olduğu soruda doğru şıkka dokunulduğunda olacaklar


      skor++;
      cevap_bekleme = 0;

      if (seviye == 1 && yanlis_eleman >= 1) {

        for (int p = 0; p < yanlis_eleman; p++) {

          if (yanlis_ingilizce[p] == yanlis_ingilizce[Dsayi] && hata_soru == true) {




            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }




            yanlis_eleman--;
            hata_soru = false;

          } else if (yanlis_ingilizce[p] == A1_ingilizce[Dsayi] && hata_soru == false) {

            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }
            yanlis_eleman--;
          }
        }


      } else if (seviye == 2 && yanlis_eleman >= 1) {
        for (int p = 0; p <= yanlis_eleman; p++) {
          if (yanlis_ingilizce[p] == yanlis_ingilizce[Dsayi] && hata_soru == true) {




            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }




            yanlis_eleman--;
            hata_soru = false;

          } else if (yanlis_ingilizce[p] == A2_ingilizce[Dsayi] && hata_soru == false) {

            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }
            yanlis_eleman--;
          }
        }

      } else if (seviye == 3 && yanlis_eleman >= 1) {
        for (int p = 0; p <= yanlis_eleman; p++) {
          if (yanlis_ingilizce[p] == yanlis_ingilizce[Dsayi] && hata_soru == true) {




            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }




            yanlis_eleman--;
            hata_soru = false;

          } else if (yanlis_ingilizce[p] == B1_ingilizce[Dsayi] && hata_soru == false) {

            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }
            yanlis_eleman--;
          }
        }
      }

      tft.setCursor(330, 70);
      tft.setTextColor(0xF81F);
      tft.setTextSize(3);
      tft.print("Dogru");
      delay(1000);

    } else if (yer == 1 && p.x < 873 && p.x > 805 && p.y < 528 && p.y > 348 && sayfa == 3 && cevap_bekleme == 1) {  //Doğru cevabın 1. şıkta olduğu soruda 2. şıkka dokunulduğunda olacaklar
      if (skor > 0)
        skor = 0;
      cevap_bekleme = 0;
      for (int i = 0; i < 21; i++) {
        if (yanlis_ingilizce[i] != A1_ingilizce[Dsayi]) {
          kontrol1 = true;

        } else {
          kontrol1 = false;
          break;
        }
      }
      if (seviye == 1 && kontrol1 == true) {

        yanlis_ingilizce[yanlis_eleman] = A1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 2 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = A2_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A2_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 3 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = B1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = B1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      }

      tft.setCursor(330, 70);
      tft.setTextColor(0x07FF);
      tft.setTextSize(3);
      tft.print("Yanlis");
      delay(1000);

    } else if (yer == 1 && p.x < 709 && p.x > 640 && p.y < 760 && p.y > 574 && sayfa == 3 && cevap_bekleme == 1) {  //Doğru cevabın 1. şıkta olduğu soruda 3. şıkka dokunulduğunda olacaklar
      if (skor > 0)
        skor = 0;
      cevap_bekleme = 0;
      for (int i = 0; i < 21; i++) {
        if (yanlis_ingilizce[i] != A1_ingilizce[Dsayi]) {
          kontrol1 = true;

        } else {
          kontrol1 = false;
          break;
        }
      }
      if (seviye == 1 && kontrol1 == true) {

        yanlis_ingilizce[yanlis_eleman] = A1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 2 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = A2_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A2_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 3 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = B1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = B1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      }
      tft.setCursor(330, 70);
      tft.setTextColor(0x07FF);
      tft.setTextSize(3);
      tft.print("Yanlis");
      delay(1000);
    }




    else if (yer == 2 && p.x < 873 && p.x > 805 && p.y < 528 && p.y > 348 && sayfa == 3 && cevap_bekleme == 1) {  //Doğru cevabın 2. şıkta olduğu soruda doğru şıkka dokunulduğunda olacaklar

      skor++;
      cevap_bekleme = 0;

      if (seviye == 1 && yanlis_eleman >= 1) {

        for (int p = 0; p < yanlis_eleman; p++) {

          if (yanlis_ingilizce[p] == yanlis_ingilizce[Dsayi] && hata_soru == true) {



            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }



            yanlis_eleman--;
            hata_soru = false;

          } else if (yanlis_ingilizce[p] == A1_ingilizce[Dsayi] && hata_soru == false) {

            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }
            yanlis_eleman--;
          }
        }


      } else if (seviye == 2 && yanlis_eleman >= 1) {
        for (int p = 0; p <= yanlis_eleman; p++) {
          if (yanlis_ingilizce[p] == yanlis_ingilizce[Dsayi] && hata_soru == true) {




            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }



            yanlis_eleman--;
            hata_soru = false;

          } else if (yanlis_ingilizce[p] == A2_ingilizce[Dsayi] && hata_soru == false) {

            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }
            yanlis_eleman--;
          }
        }

      } else if (seviye == 3 && yanlis_eleman >= 1) {
        for (int p = 0; p <= yanlis_eleman; p++) {
          if (yanlis_ingilizce[p] == yanlis_ingilizce[Dsayi] && hata_soru == true) {




            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }



            yanlis_eleman--;
            hata_soru = false;

          } else if (yanlis_ingilizce[p] == B1_ingilizce[Dsayi] && hata_soru == false) {

            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }
            yanlis_eleman--;
          }
        }
      }


      tft.setCursor(330, 70);
      tft.setTextColor(0xF81F);
      tft.setTextSize(3);
      tft.print("Dogru");
      delay(1000);

    } else if (yer == 2 && p.x < 709 && p.x > 646 && p.y < 372 && p.y > 189 && sayfa == 3 && cevap_bekleme == 1) {  //Doğru cevabın 2. şıkta olduğu soruda 1. şıkka dokunulduğunda olacaklar
      if (skor > 0)
        skor = 0;
      cevap_bekleme = 0;

      for (int i = 0; i < 21; i++) {
        if (yanlis_ingilizce[i] != A1_ingilizce[Dsayi]) {
          kontrol1 = true;

        } else {
          kontrol1 = false;
          break;
        }
      }
      if (seviye == 1 && kontrol1 == true) {

        yanlis_ingilizce[yanlis_eleman] = A1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 2 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = A2_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A2_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 3 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = B1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = B1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      }

      tft.setCursor(330, 70);
      tft.setTextColor(0x07FF);
      tft.setTextSize(3);
      tft.print("Yanlis");
      delay(1000);

    } else if (yer == 2 && p.x < 709 && p.x > 640 && p.y < 760 && p.y > 574 && sayfa == 3 && cevap_bekleme == 1) {  //Doğru cevabın 2. şıkta olduğu soruda 3. şıkka dokunulduğunda olacaklar
      if (skor > 0)
        skor = 0;
      cevap_bekleme = 0;

      for (int i = 0; i < 21; i++) {
        if (yanlis_ingilizce[i] != A1_ingilizce[Dsayi]) {
          kontrol1 = true;

        } else {
          kontrol1 = false;
          break;
        }
      }
      if (seviye == 1 && kontrol1 == true) {

        yanlis_ingilizce[yanlis_eleman] = A1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 2 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = A2_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A2_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 3 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = B1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = B1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      }

      tft.setCursor(330, 70);
      tft.setTextColor(0x07FF);
      tft.setTextSize(3);
      tft.print("Yanlis");
      delay(1000);
    }






    else if (yer == 3 && p.x < 709 && p.x > 640 && p.y < 760 && p.y > 574 && sayfa == 3 && cevap_bekleme == 1) {  //Doğru cevabın 3. şıkta olduğu soruda doğru şıkka dokunulduğunda olacaklar

      skor++;
      cevap_bekleme = 0;

      if (seviye == 1 && yanlis_eleman >= 1) {

        for (int p = 0; p < yanlis_eleman; p++) {

          if (yanlis_ingilizce[p] == yanlis_ingilizce[Dsayi] && hata_soru == true) {




            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }




            yanlis_eleman--;
            hata_soru = false;

          } else if (yanlis_ingilizce[p] == A1_ingilizce[Dsayi] && hata_soru == false) {

            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }
            yanlis_eleman--;
          }
        }


      } else if (seviye == 2 && yanlis_eleman >= 1) {
        for (int p = 0; p <= yanlis_eleman; p++) {
          if (yanlis_ingilizce[p] == yanlis_ingilizce[Dsayi] && hata_soru == true) {




            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }




            yanlis_eleman--;
            hata_soru = false;

          } else if (yanlis_ingilizce[p] == A2_ingilizce[Dsayi] && hata_soru == false) {

            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }
            yanlis_eleman--;
          }
        }

      } else if (seviye == 3 && yanlis_eleman >= 1) {
        for (int p = 0; p <= yanlis_eleman; p++) {
          if (yanlis_ingilizce[p] == yanlis_ingilizce[Dsayi] && hata_soru == true) {




            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }




            yanlis_eleman--;
            hata_soru = false;

          } else if (yanlis_ingilizce[p] == B1_ingilizce[Dsayi] && hata_soru == false) {

            yanlis_ingilizce[p] = "bos";
            yanlis_turkce[p] = "bos";
            for (int y = p; y < yanlis_eleman; y++) {

              yanlis_ingilizce[y] = yanlis_ingilizce[y + 1];
              yanlis_turkce[y] = yanlis_turkce[y + 1];
            }
            yanlis_eleman--;
          }
        }
      }

      tft.setCursor(330, 70);
      tft.setTextColor(0xF81F);
      tft.setTextSize(3);
      tft.print("Dogru");
      delay(1000);

    } else if (yer == 3 && p.x < 709 && p.x > 646 && p.y < 372 && p.y > 189 && sayfa == 3 && cevap_bekleme == 1) {  //Doğru cevabın 3. şıkta olduğu soruda 1. şıkka dokunulduğunda olacaklar

      if (skor > 0)
        skor = 0;
      cevap_bekleme = 0;

      for (int i = 0; i < 21; i++) {
        if (yanlis_ingilizce[i] != A1_ingilizce[Dsayi]) {
          kontrol1 = true;

        } else {
          kontrol1 = false;
          break;
        }
      }
      if (seviye == 1 && kontrol1 == true) {

        yanlis_ingilizce[yanlis_eleman] = A1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 2 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = A2_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A2_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 3 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = B1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = B1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      }

      tft.setCursor(330, 70);
      tft.setTextColor(0x07FF);
      tft.setTextSize(3);
      tft.print("Yanlis");
      delay(1000);
    } else if (yer == 3 && p.x < 873 && p.x > 805 && p.y < 528 && p.y > 348 && sayfa == 3 && cevap_bekleme == 1) {  //Doğru cevabın 3. şıkta olduğu soruda 2. şıkka dokunulduğunda olacaklar
      if (skor > 0)
        skor--;
      cevap_bekleme = 0;

      for (int i = 0; i < 21; i++) {
        if (yanlis_ingilizce[i] != A1_ingilizce[Dsayi]) {
          kontrol1 = true;

        } else {
          kontrol1 = false;
          break;
        }
      }
      if (seviye == 1 && kontrol1 == true) {

        yanlis_ingilizce[yanlis_eleman] = A1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 2 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = A2_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = A2_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      } else if (seviye == 3 && kontrol1 == true) {
        yanlis_ingilizce[yanlis_eleman] = B1_ingilizce[Dsayi];
        yanlis_turkce[yanlis_eleman] = B1_turkce[Dsayi];
        kontrol1 = false;
        yanlis_eleman++;
      }

      tft.setCursor(330, 70);
      tft.setTextColor(0x07FF);
      tft.setTextSize(3);
      tft.print("Yanlis");
      delay(1000);
    }

    if (cevap_bekleme == 0) {  // Soru sayfası açıldıktan sonra cevap verilene kadar sayfanın değişmemesi için

      if (sayfa == 3) {
        for (int u = 0; u < 20; u++) {
          Serial.print(yanlis_ingilizce[u] + ",");
        }
        Serial.println(" ");
        Serial.print("eleman:");
        Serial.println(yanlis_eleman);
        Serial.print("sayac:");
        Serial.println(yanlis_sayac);
      }

      if (sayfa == 3) {
        //Dizi den kelime seçmek için random komutunu kullanıyorum
        cevap_bekleme = 1;

        randomSeed(analogRead(A13));
        Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
        randomSeed(analogRead(A14));
        Y1sayi = random(0, 20);  // Yanlış olan birinci şık
        randomSeed(analogRead(A15));
        Ysayi = random(0, 20);  // Yanlış olan ikinci şık
        randomSeed(analogRead(A12));
        yer = random(1, 4);  // Doğru cevabın hangi şıkta olaağını belirler



        while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
          randomSeed(analogRead(A13));
          Dsayi = random(0, 20);
          randomSeed(analogRead(A14));
          Y1sayi = random(0, 20);
          randomSeed(analogRead(A15));
          Ysayi = random(0, 20);
        }
        onceki_kelime = Dsayi;






        if (seviye == 1) {  //A1 seviyesinin soru ekranı
          tft.fillScreen(0x0000);

          tft.fillRect(0, 20, 78, 40, 0xFFFF);
          tft.setCursor(5, 30);
          tft.setTextColor(0x0000);
          tft.setTextSize(3);
          tft.print("Geri");


          if (yer == 1) {  // A1 seviyesinde doğru cevap 1. şıkta olan soru komutları
            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);




            if (yanlis_eleman <= 5 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 4) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);


              } else {
                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
                hata_soru = true;
              }

            } else if (yanlis_eleman <= 10 && yanlis_eleman >= 1) {

              if (yanlis_sayac < 3) {
                yanlis_sayac++;

                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık




                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
                hata_soru = true;
              }



            } else if (yanlis_eleman <= 15 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 2) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık




                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
                hata_soru = true;
              }
            } else {
              randomSeed(analogRead(A13));
              Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
              randomSeed(analogRead(A14));
              Y1sayi = random(0, 20);  // Yanlış olan birinci şık
              randomSeed(analogRead(A15));
              Ysayi = random(0, 20);  // Yanlış olan ikinci şık




              while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                randomSeed(analogRead(A13));
                Dsayi = random(0, 20);
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);
              }
              onceki_kelime = Dsayi;


              tft.setCursor(100, 80);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(4);
              tft.print(A1_ingilizce[Dsayi]);

              tft.setCursor(30, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A1_turkce[Dsayi]);

              tft.setCursor(130, 270);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A1_turkce[Y1sayi]);

              tft.setCursor(260, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A1_turkce[Ysayi]);
            }


          } else if (yer == 2) {  // A1 seviyesinde doğru cevap 2. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


            if (yanlis_eleman <= 5 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 4) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);


              } else {
                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
                hata_soru = true;
              }

            } else if (yanlis_eleman <= 10 && yanlis_eleman >= 1) {

              if (yanlis_sayac < 3) {
                yanlis_sayac++;

                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
                hata_soru = true;
              }



            } else if (yanlis_eleman <= 15 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 2) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);
                hata_soru = true;
              }
            } else {
              randomSeed(analogRead(A13));
              Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
              randomSeed(analogRead(A14));
              Y1sayi = random(0, 20);  // Yanlış olan birinci şık
              randomSeed(analogRead(A15));
              Ysayi = random(0, 20);  // Yanlış olan ikinci şık




              while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                randomSeed(analogRead(A13));
                Dsayi = random(0, 20);
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);
              }
              onceki_kelime = Dsayi;


              tft.setCursor(100, 80);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(4);
              tft.print(A1_ingilizce[Dsayi]);

              tft.setCursor(30, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A1_turkce[Y1sayi]);

              tft.setCursor(130, 270);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A1_turkce[Dsayi]);

              tft.setCursor(260, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A1_turkce[Ysayi]);
            }


          } else if (yer == 3) {  // A1 seviyesinde doğru cevap 3. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


            if (yanlis_eleman <= 5 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 4) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Dsayi]);


              } else {
                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);
                hata_soru = true;
              }

            } else if (yanlis_eleman <= 10 && yanlis_eleman >= 1) {

              if (yanlis_sayac < 3) {
                yanlis_sayac++;

                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Dsayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);
                hata_soru = true;
              }



            } else if (yanlis_eleman <= 15 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 2) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Dsayi]);
                hata_soru = true;
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);
              }
            } else {
              randomSeed(analogRead(A13));
              Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
              randomSeed(analogRead(A14));
              Y1sayi = random(0, 20);  // Yanlış olan birinci şık
              randomSeed(analogRead(A15));
              Ysayi = random(0, 20);  // Yanlış olan ikinci şık




              while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                randomSeed(analogRead(A13));
                Dsayi = random(0, 20);
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);
              }
              onceki_kelime = Dsayi;


              tft.setCursor(100, 80);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(4);
              tft.print(A1_ingilizce[Dsayi]);

              tft.setCursor(30, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A1_turkce[Y1sayi]);

              tft.setCursor(130, 270);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A1_turkce[Ysayi]);

              tft.setCursor(260, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A1_turkce[Dsayi]);
            }
          }
        } else if (seviye == 2) {  //A2 seviyesinin soru ekranı
          tft.fillScreen(0x0000);

          tft.fillRect(0, 20, 78, 40, 0xFFFF);
          tft.setCursor(5, 30);
          tft.setTextColor(0x0000);
          tft.setTextSize(3);
          tft.print("Geri");

          if (yer == 1) {  // A2 seviyesinde doğru cevap 1. şıkta olan soru komutları
            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);



            if (yanlis_eleman <= 5 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 4) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A2_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);


              } else {
                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
                hata_soru = true;
              }

            } else if (yanlis_eleman <= 10 && yanlis_eleman >= 1) {

              if (yanlis_sayac < 3) {
                yanlis_sayac++;

                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A2_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık




                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
                hata_soru = true;
              }



            } else if (yanlis_eleman <= 15 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 2) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A2_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık




                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
                hata_soru = true;
              }
            } else {
              randomSeed(analogRead(A13));
              Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
              randomSeed(analogRead(A14));
              Y1sayi = random(0, 20);  // Yanlış olan birinci şık
              randomSeed(analogRead(A15));
              Ysayi = random(0, 20);  // Yanlış olan ikinci şık




              while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                randomSeed(analogRead(A13));
                Dsayi = random(0, 20);
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);
              }
              onceki_kelime = Dsayi;


              tft.setCursor(100, 80);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(4);
              tft.print(A2_ingilizce[Dsayi]);

              tft.setCursor(30, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A2_turkce[Dsayi]);

              tft.setCursor(130, 270);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A2_turkce[Y1sayi]);

              tft.setCursor(260, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A2_turkce[Ysayi]);
            }


          } else if (yer == 2) {  // A2 seviyesinde doğru cevap 2. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


            if (yanlis_eleman <= 5 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 4) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A2_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);


              } else {
                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
                hata_soru = true;
              }

            } else if (yanlis_eleman <= 10 && yanlis_eleman >= 1) {

              if (yanlis_sayac < 3) {
                yanlis_sayac++;

                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A2_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
                hata_soru = true;
              }



            } else if (yanlis_eleman <= 15 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 2) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A2_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);
                hata_soru = true;
              }
            } else {
              randomSeed(analogRead(A13));
              Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
              randomSeed(analogRead(A14));
              Y1sayi = random(0, 20);  // Yanlış olan birinci şık
              randomSeed(analogRead(A15));
              Ysayi = random(0, 20);  // Yanlış olan ikinci şık




              while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                randomSeed(analogRead(A13));
                Dsayi = random(0, 20);
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);
              }
              onceki_kelime = Dsayi;


              tft.setCursor(100, 80);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(4);
              tft.print(A2_ingilizce[Dsayi]);

              tft.setCursor(30, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A2_turkce[Y1sayi]);

              tft.setCursor(130, 270);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A2_turkce[Dsayi]);

              tft.setCursor(260, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A2_turkce[Ysayi]);
            }

          } else if (yer == 3) {  // A2 seviyesinde doğru cevap 3. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);

            if (yanlis_eleman <= 5 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 4) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A2_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Dsayi]);


              } else {
                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);
                hata_soru = true;
              }

            } else if (yanlis_eleman <= 10 && yanlis_eleman >= 1) {

              if (yanlis_sayac < 3) {
                yanlis_sayac++;

                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A2_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Dsayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);
                hata_soru = true;
              }



            } else if (yanlis_eleman <= 15 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 2) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(A2_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Dsayi]);
                hata_soru = true;
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(A2_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);
              }
            } else {
              randomSeed(analogRead(A13));
              Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
              randomSeed(analogRead(A14));
              Y1sayi = random(0, 20);  // Yanlış olan birinci şık
              randomSeed(analogRead(A15));
              Ysayi = random(0, 20);  // Yanlış olan ikinci şık




              while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                randomSeed(analogRead(A13));
                Dsayi = random(0, 20);
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);
              }
              onceki_kelime = Dsayi;


              tft.setCursor(100, 80);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(4);
              tft.print(A2_ingilizce[Dsayi]);

              tft.setCursor(30, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A2_turkce[Y1sayi]);

              tft.setCursor(130, 270);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A2_turkce[Ysayi]);

              tft.setCursor(260, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(A2_turkce[Dsayi]);
            }
          }
        } else if (seviye == 3) { //B1 seviyesinin soru ekranı
          tft.fillScreen(0x0000);

          tft.fillRect(0, 20, 78, 40, 0xFFFF);
          tft.setCursor(5, 30);
          tft.setTextColor(0x0000);
          tft.setTextSize(3);
          tft.print("Geri");

          if (yer == 1) {  //  B1 seviyesinde doğru cevap 1. şıkta olan soru komutları
            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);



            if (yanlis_eleman <= 5 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 4) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(B1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);


              } else {
                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
                hata_soru = true;
              }

            } else if (yanlis_eleman <= 10 && yanlis_eleman >= 1) {

              if (yanlis_sayac < 3) {
                yanlis_sayac++;

                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(B1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık




                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
                hata_soru = true;
              }



            } else if (yanlis_eleman <= 15 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 2) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(B1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık




                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
                hata_soru = true;
              }
            } else {
              randomSeed(analogRead(A13));
              Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
              randomSeed(analogRead(A14));
              Y1sayi = random(0, 20);  // Yanlış olan birinci şık
              randomSeed(analogRead(A15));
              Ysayi = random(0, 20);  // Yanlış olan ikinci şık




              while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                randomSeed(analogRead(A13));
                Dsayi = random(0, 20);
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);
              }
              onceki_kelime = Dsayi;


              tft.setCursor(100, 80);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(4);
              tft.print(B1_ingilizce[Dsayi]);

              tft.setCursor(30, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(B1_turkce[Dsayi]);

              tft.setCursor(130, 270);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(B1_turkce[Y1sayi]);

              tft.setCursor(260, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(B1_turkce[Ysayi]);
            }

          } else if (yer == 2) {  // B1 seviyesinde doğru cevap 2. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


            if (yanlis_eleman <= 5 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 4) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(B1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);


              } else {
                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
                hata_soru = true;
              }

            } else if (yanlis_eleman <= 10 && yanlis_eleman >= 1) {

              if (yanlis_sayac < 3) {
                yanlis_sayac++;

                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(B1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
                hata_soru = true;
              }



            } else if (yanlis_eleman <= 15 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 2) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(B1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);
                hata_soru = true;
              }
            } else {
              randomSeed(analogRead(A13));
              Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
              randomSeed(analogRead(A14));
              Y1sayi = random(0, 20);  // Yanlış olan birinci şık
              randomSeed(analogRead(A15));
              Ysayi = random(0, 20);  // Yanlış olan ikinci şık




              while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                randomSeed(analogRead(A13));
                Dsayi = random(0, 20);
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);
              }
              onceki_kelime = Dsayi;


              tft.setCursor(100, 80);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(4);
              tft.print(B1_ingilizce[Dsayi]);

              tft.setCursor(30, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(B1_turkce[Y1sayi]);

              tft.setCursor(130, 270);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(B1_turkce[Dsayi]);

              tft.setCursor(260, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(B1_turkce[Ysayi]);
            }



          } else if (yer == 3) {  // B1 seviyesinde doğru cevap 3. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


            if (yanlis_eleman <= 5 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 4) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(B1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Dsayi]);


              } else {
                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);
                hata_soru = true;
              }

            } else if (yanlis_eleman <= 10 && yanlis_eleman >= 1) {

              if (yanlis_sayac < 3) {
                yanlis_sayac++;

                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(B1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Dsayi]);
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);
                hata_soru = true;
              }



            } else if (yanlis_eleman <= 15 && yanlis_eleman >= 1) {
              if (yanlis_sayac < 2) {
                yanlis_sayac++;
                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(B1_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Dsayi]);
                hata_soru = true;
              } else {

                yanlis_sayac = 0;
                randomSeed(analogRead(A13));
                Dsayi = random(0, yanlis_eleman);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);  // Yanlış olan birinci şık
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);  // Yanlış olan ikinci şık





                while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi || yanlis_ingilizce[Dsayi] == "bos") {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                  randomSeed(analogRead(A13));
                  Dsayi = random(0, yanlis_eleman);
                  randomSeed(analogRead(A14));
                  Y1sayi = random(0, 20);
                  randomSeed(analogRead(A15));
                  Ysayi = random(0, 20);
                }
                onceki_kelime = Dsayi;


                tft.setCursor(100, 80);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(4);
                tft.print(yanlis_ingilizce[Dsayi]);

                tft.setCursor(30, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Y1sayi]);

                tft.setCursor(130, 270);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(B1_turkce[Ysayi]);

                tft.setCursor(260, 200);
                tft.setTextColor(0xFFFF);
                tft.setTextSize(3);
                tft.print(yanlis_turkce[Dsayi]);
              }
            } else {
              randomSeed(analogRead(A13));
              Dsayi = random(0, 20);  // İngilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
              randomSeed(analogRead(A14));
              Y1sayi = random(0, 20);  // Yanlış olan birinci şık
              randomSeed(analogRead(A15));
              Ysayi = random(0, 20);  // Yanlış olan ikinci şık




              while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // Eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
                randomSeed(analogRead(A13));
                Dsayi = random(0, 20);
                randomSeed(analogRead(A14));
                Y1sayi = random(0, 20);
                randomSeed(analogRead(A15));
                Ysayi = random(0, 20);
              }
              onceki_kelime = Dsayi;


              tft.setCursor(100, 80);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(4);
              tft.print(B1_ingilizce[Dsayi]);

              tft.setCursor(30, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(B1_turkce[Y1sayi]);

              tft.setCursor(130, 270);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(B1_turkce[Ysayi]);

              tft.setCursor(260, 200);
              tft.setTextColor(0xFFFF);
              tft.setTextSize(3);
              tft.print(B1_turkce[Dsayi]);
            }
          }
        }
      }
    }
   
    p.x = 0;
    p.y = 0;
  }


   
  delay(100);
}


