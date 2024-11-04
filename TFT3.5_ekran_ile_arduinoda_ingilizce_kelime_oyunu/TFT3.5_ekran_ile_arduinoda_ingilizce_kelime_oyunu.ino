//Kütüphaneler
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include "TouchScreen.h"
#include <stdint.h>



MCUFRIEND_kbv tft(A3, A2, A1, A0, A4);
TouchScreen ts = TouchScreen(9, A2, A3, 8, 300);

//uygulamada kullanılar kelimeler
String A1_ingilizce[] = { "Know", "Think", "Buy", "Bring", "Catch", "Run", "Drink",
                          "Swim", "Break", "Forget", "Wear", "Fall", "Eat", "Take", "Lose",
                          "Try", "Hear", "Oturmak", "Alone", "Angry" };
String A1_turkce[] = { "Bilmek", "Dusunmek", "Satin almak", "Getirmek", "Yakalamak",
                       "Kosmak", "Icmek", "Yuzmek", "Kirmak", "Unutmak", "Giymek",
                       "Dusmek", "Yemek", "Almak", "Kaybetmek", "Denemek", "Duymak",
                       "Sit", "Yalniz", "Kizgin" };

String A2_ingilizce[] = { "Accept", "Accident", "Adventure", "Agree", "Begin", "Believe",
                          "Bite", "Brain", "Busy", "Cash", "Choose", "Climb", "Cut", "Cute",
                          "Dangerous", "Delete", "Die", "Expensive", "Explain", "Fill" };
String A2_turkce[] = { "kabul etmek", "kaza", "macera", "anlasmak", "baslamak", "inanmak",
                       "isirmak", "beyin", "mesgul", "nakit", "secmek", "tirmanmak", "kesmek",
                       "sevimli", "tehlikeli", "silmek", "olmek", "pahali", "aciklamak", "doldurmak" };

String B1_ingilizce[] = { "advice", "art", "attack", "blood", "destroy", "engine", "import", "low",
                          "peace", "poison", "population", "publish", "remove", "result", "search",
                          "space", "tool", "trade", "truck", "wide" };
String B1_turkce[] = { "tavsiye", "sanat", "saldiri", "kan", "yikmak", "motor", "ithalat", "dusuk",
                       "baris", "zehir", "populasyon", "yayinlamak", "kaldirmak", "sonuc", "arastirmak",
                       "bosluk", "alet", "ticaret", "kamyon", "genis" };


//uygulamadaki değişkenler
short sayfa;   //sayfa değişkeni 1(giriş),2(seviye seçimi)ve 3(soru cevap sayfası) olarak kullanıldı
short seviye;  // seviye değişkeni 1(A1),2(A2)ve 3(B1) olarak kullanıldı
short skor;    // soru bildikçe 1 arttırıldı yanlış cevapta sıfırlandı
// şıklarda kullanılan kelimelerin dizi sırası için kullanıldı
short Dsayi;
short Ysayi;
short Y1sayi;

short yer;            // doğru kelimenin  hangi şıkta olacağını belirlemek için kullanıldı 1(a),2(b) ve 3(c).
short cevap_bekleme;  //soru cevap sayfası yüklendikten sonra cevap verilene kadar sayfanın değişmemesi için kullanılı
short onceki_kelime;  // peşpeşe aynı ingilizce kelime gelmemesi için kullanıldı


void setup() {
  // ekran ve arduino kart bağlantıları
  tft.reset();
  uint8_t ID = tft.readID();
  tft.begin(ID);
  Serial.begin(9600);


  sayfa = 1;
  skor = 0;
  cevap_bekleme = 0;

  //giriş sayfası
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
  TSPoint p = ts.getPoint();  //ekranda tokunulan kısımdaki pixelin x ve y kordinatını almak için

  if (p.z > ts.pressureThreshhold) {  //ekrana baskı kuvveti bellirli bi orandan sonra ekranın algılaması için
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

    delay(100);


    //giriş sayfasından seviye seçim sayfasına geçiş
    if (p.x > 695 && p.x < 780 && p.y > 400 && p.y < 620 && sayfa == 1) {
      sayfa = 2;
      tft.fillScreen(0x0000);
      tft.setCursor(60, 70);
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

      tft.drawRect(3, 20, 78, 40, 0xFFFF);
      tft.setCursor(5, 30);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(3);
      tft.print("Geri");
      p.x = 0;
      p.y = 0;
    }

    delay(100);

    //seviye seçme sayfasında yani sayfa 2 de basılan pixelin kordinatına göre deviye seçimi
    if (sayfa == 2) {
      if (p.x > 640 && p.x < 715 && p.y > 265 && p.y < 335) {  //A1 seviyesi
        sayfa = 3;
        seviye = 1;
        cevap_bekleme = 0;
        p.x = 0;
        p.y = 0;
      }

      else if (p.x > 630 && p.x < 740 && p.y > 465 && p.y < 545) {  //A2 seviyesi
        sayfa = 3;
        seviye = 2;
        cevap_bekleme = 0;
        p.x = 0;
        p.y = 0;
      }

      else if (p.x > 640 && p.x < 736 && p.y > 650 && p.y < 744) {  //B1 seviyesi

        sayfa = 3;
        seviye = 3;
        cevap_bekleme = 0;
        p.x = 0;
        p.y = 0;
      }
    }
    delay(100);
    // soru cevap sayafasıdaki yani sayfa 3 teki geri butonuna basınca sayfa 2 yi açması için
    if (p.x < 313 && p.x > 224 && p.y < 240 && p.y > 163 && sayfa == 3) {
      sayfa = 2;
      tft.fillScreen(0x0000);
      tft.setCursor(60, 70);
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

      tft.drawRect(3, 20, 78, 40, 0xFFFF);
      tft.setCursor(5, 30);
      tft.setTextColor(0xFFFF);
      tft.setTextSize(3);
      tft.print("Geri");

      cevap_bekleme = 0;
      skor = 0;
      p.x = 0;
      p.y = 0;
    }
    if (p.x < 313 && p.x > 224 && p.y < 240 && p.y > 163 && sayfa == 2) {
      sayfa = 1;

      tft.drawRect(3, 20, 78, 40, 0xFFFF);
      tft.setCursor(5, 30);
      tft.setTextColor(0xFFFF);
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


    /* cevaba dokunduktan sonra pixel kordinatına göre doğru yanlış kontrolü için 
    not:cevap kontrolü soru kodlarında önce yazılmıştır çünkü soru kodlarından sonra yazıldığı zaman cevaba 2 defa tıklandıktan sonra diğer soru sayfası açılıyordu.*/
    if (yer == 1 && p.x < 709 && p.x > 646 && p.y < 372 && p.y > 189 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 1. şıkta olduğu soruda doğru şıkka dokunulduğunda olacaklar

      skor++;
      cevap_bekleme = 0;


    } else if (yer == 1 && p.x < 873 && p.x > 805 && p.y < 528 && p.y > 348 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 1. şıkta olduğu soruda yanlış şıkka dokunulduğunda olacaklar

      skor = 0;
      cevap_bekleme = 0;


    } else if (yer == 1 && p.x < 709 && p.x > 640 && p.y < 760 && p.y > 574 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 1. şıkta olduğu soruda yanlış şıkka dokunulduğunda olacaklar

      skor = 0;
      cevap_bekleme = 0;


    }




    else if (yer == 2 && p.x < 873 && p.x > 805 && p.y < 528 && p.y > 348 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 2. şıkta olduğu soruda doğru şıkka dokunulduğunda olacaklar

      skor++;
      cevap_bekleme = 0;


    } else if (yer == 2 && p.x < 709 && p.x > 646 && p.y < 372 && p.y > 189 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 2. şıkta olduğu soruda yanlış şıkka dokunulduğunda olacaklar

      skor = 0;
      cevap_bekleme = 0;


    } else if (yer == 2 && p.x < 709 && p.x > 640 && p.y < 760 && p.y > 574 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 2. şıkta olduğu soruda yanlış şıkka dokunulduğunda olacaklar

      skor = 0;
      cevap_bekleme = 0;


    }






    else if (yer == 3 && p.x < 709 && p.x > 640 && p.y < 760 && p.y > 574 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 3. şıkta olduğu soruda doğru şıkka dokunulduğunda olacaklar

      skor++;
      cevap_bekleme = 0;


    } else if (yer == 3 && p.x < 709 && p.x > 646 && p.y < 372 && p.y > 189 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 3. şıkta olduğu soruda yanlış şıkka dokunulduğunda olacaklar

      skor = 0;
      cevap_bekleme = 0;


    } else if (yer == 3 && p.x < 873 && p.x > 805 && p.y < 528 && p.y > 348 && sayfa == 3 && cevap_bekleme == 1) {  //doğru cevabın 3. şıkta olduğu soruda yanlış şıkka dokunulduğunda olacaklar

      skor--;
      cevap_bekleme = 0;
    }

    if (cevap_bekleme == 0) {  // soru sayfası açıldıktan sonra cevap verilene kadar sayfanın değişmemesi için

      if (sayfa == 3) {
        //dizi den kelime seçmek için random komutunu kullanıyorum
        cevap_bekleme = 1;
        randomSeed(analogRead(A13));
        Dsayi = random(0, 20);  // ingilizce kelime ve doğru olan şıkkın dizi sırasındaki sayı
        randomSeed(analogRead(A14));
        Y1sayi = random(0, 20);  // yanlış olan birinci şık
        randomSeed(analogRead(A15));
        Ysayi = random(0, 20);  // yanlış olan ikinci şık
        randomSeed(analogRead(A12));
        yer = random(1, 4);  // doğru cevabın hangi şıkta olaağını belirler


        while (Dsayi == Y1sayi || Dsayi == Ysayi || Ysayi == Y1sayi || onceki_kelime == Dsayi) {  // eğer şıklar aynı olursa ve soru kelimesi önceki soru ile aynı olursa  random komutu ile tekrardan sayı alıyorum
          randomSeed(analogRead(A13));
          Dsayi = random(0, 20);
          randomSeed(analogRead(A14));
          Y1sayi = random(0, 20);
          randomSeed(analogRead(A15));
          Ysayi = random(0, 20);
        }
        onceki_kelime = Dsayi;  //


        if (seviye == 1) {  //A1 seviyesinin soru ekranın
          tft.fillScreen(0x0000);

          tft.drawRect(3, 20, 78, 40, 0xFFFF);
          tft.setCursor(5, 30);
          tft.setTextColor(0xFFFF);
          tft.setTextSize(3);
          tft.print("Geri");


          if (yer == 1) {  // A1 seviyesinde doğru cevap 1. şıkta olan soru komutları
            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);



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


          } else if (yer == 2) {  // A1 seviyesinde doğru cevap 2. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


            tft.setCursor(100, 80);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(4);
            tft.print(A1_ingilizce[Dsayi]);

            tft.setCursor(30, 200);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print(A1_turkce[Ysayi]);

            tft.setCursor(130, 270);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print(A1_turkce[Dsayi]);

            tft.setCursor(260, 200);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print(A1_turkce[Y1sayi]);


          } else if (yer == 3) {  // A1 seviyesinde doğru cevap 3. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


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




        } else if (seviye == 2) {  //A2 seviyesinin soruları
          tft.fillScreen(0x0000);

          tft.drawRect(3, 20, 78, 40, 0xFFFF);
          tft.setCursor(5, 30);
          tft.setTextColor(0xFFFF);
          tft.setTextSize(3);
          tft.print("Geri");

          if (yer == 1) {  // A2 seviyesinde doğru cevap 1. şıkta olan soru komutları
            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);



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
          } else if (yer == 2) {  // A2 seviyesinde doğru cevap 2. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


            tft.setCursor(100, 80);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(4);
            tft.print(A2_ingilizce[Dsayi]);

            tft.setCursor(30, 200);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print(A2_turkce[Ysayi]);

            tft.setCursor(130, 270);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print(A2_turkce[Dsayi]);

            tft.setCursor(260, 200);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print(A2_turkce[Y1sayi]);

          } else if (yer == 3) {  // A2 seviyesinde doğru cevap 2. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


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

        } else if (seviye == 3) {  //B1 seviyesinin soruları
          tft.fillScreen(0x0000);

          tft.drawRect(3, 20, 78, 40, 0xFFFF);
          tft.setCursor(5, 30);
          tft.setTextColor(0xFFFF);
          tft.setTextSize(3);
          tft.print("Geri");

          if (yer == 1) {  //  B1 seviyesinde doğru cevap 1. şıkta olan soru komutları
            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);



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

          } else if (yer == 2) {  // B1 seviyesinde doğru cevap 2. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


            tft.setCursor(100, 80);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(4);
            tft.print(B1_ingilizce[Dsayi]);

            tft.setCursor(30, 200);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print(B1_turkce[Ysayi]);

            tft.setCursor(130, 270);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print(B1_turkce[Dsayi]);

            tft.setCursor(260, 200);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print(B1_turkce[Y1sayi]);
          } else if (yer == 3) {  // B1 seviyesinde doğru cevap 3. şıkta olan soru komutları

            tft.setCursor(330, 30);
            tft.setTextColor(0xFFFF);
            tft.setTextSize(3);
            tft.print("skor=");
            tft.print(skor);


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
      p.x = 0;
      p.y = 0;
    }




    delay(100);
  }
}
