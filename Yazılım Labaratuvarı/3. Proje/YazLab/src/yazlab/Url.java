/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package yazlab;

import java.io.IOException;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

/**
 *
 * @author ILYAS MAMMADOV
 */
public class Url extends Thread{
    String url;
    int puan;
    Kelime[] kelimeler = new Kelime[10];
    Document doc;
    Url[] altUrller = new Url[200];
    int derinlik;
    
    Url(String url, Kelime[] kelimeler, int derinlik){
        this.url = url;
        this.kelimeler = kelimeler;
        this.derinlik = derinlik;
    }
    
    @Override
    public void run(){
        try{
            doc = Jsoup.connect(url).get();
            if(derinlik <= 3){
                kelimeTara();
                System.out.println("Derinlik: " + derinlik);
            }
            if(derinlik <= 2){
                Elements elementler;
                elementler = doc.select("a[href]");
                altaDallan(elementler);
            }
        } catch (IOException e){
            this.interrupt();
        }
        
        /*boolean durum;
        try{
            while(true){
                durum = true;
                for(Url link: altUrller){
                    if(!link.isInterrupted()){
                        durum = false;
                    }
                }
                if(durum == true){
                    break;
                }
                Thread.sleep(500);
            }
        } catch(InterruptedException e){
            //bos...
        }
        this.interrupt();*/
    }
    
    private void altaDallan(Elements elementler){
        //try{
            int i = 0;
            String url;
            for(Element link: elementler){
                url = link.attr("href");
                if(url.indexOf("http") != -1){
                    altUrller[i] = new Url(url, kelimeler, derinlik+1);
                    altUrller[i].start();
                    i++;
                }
            }
        /*} catch(InterruptedException e){
            //bos...
        }*/
        System.out.println("Alt linkler bitti.****************************************");
    }
    
    private void kelimeTara(){
        String veri = doc.text();
        System.out.println("URL - " + this.url);
        for(Kelime kelime: kelimeler){
            for(int pos = 0; pos < veri.length() && pos != -1;){
                pos = veri.indexOf(kelime.kelime, pos+1);
                kelime.frekans++;
            }
            System.out.println(kelime.kelime + ": " + kelime.frekans);
        }
        puanlama();
    }
    
    private void puanlama(){
        int toplam = 0;
        for(Kelime kelime: kelimeler){
            toplam += kelime.frekans;
        }
        this.puan = Math.round(toplam/kelimeler.length);
        System.out.println("Puan: " + this.puan);
    }
}
