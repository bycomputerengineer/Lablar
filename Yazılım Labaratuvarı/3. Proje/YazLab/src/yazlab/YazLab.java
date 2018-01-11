/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package yazlab;

import java.util.Scanner;

/**
 *
 * @author ILYAS MAMMADOV
 */
public class YazLab {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        Scanner scan = new Scanner(System.in);
        
        int kelimeSayisi;
        System.out.print("Aranacak kelime sayisini giriniz: ");
        kelimeSayisi = scan.nextInt();
        Kelime[] kelimeler = new Kelime[kelimeSayisi]; 
        
        //kelimelerin alinmasi
        for(int i = 0; i < kelimeSayisi; i++){
            kelimeler[i] = new Kelime();
            System.out.print("Kelime: ");
            kelimeler[i].kelime = scan.next();
        }
        
        int linkSayisi;
        System.out.print("Aranacak link sayisini giriniz: ");
        linkSayisi = scan.nextInt();
        Url[] linkler = new Url[linkSayisi];
        
        //linklerin alinmasi
        String url;
        for(int i = 0; i < linkSayisi; i++){
            System.out.print("Link: ");
            url = scan.next();
            linkler[i] = new Url(url, kelimeler, 1);
        }
        
        for(int i = 0; i < linkSayisi; i++){
            linkler[i].start();
        }
        
        /*boolean durum;
        try{
            while(true){
                durum = true;
                for(Url url1: linkler){
                    if(!url1.isInterrupted()){
                        durum = false;
                    }
                }
                if(durum == true){
                    for(Url url2: linkler){
                        yazdir(url2);
                    }
                    break;
                }
                Thread.sleep(100);
            }
        } catch(InterruptedException e){
            //bos...
        }*/
        
        /*
        https://www.w3schools.com/html/default.asp
        https://www.w3schools.com/html/html_intro.asp
        https://www.w3schools.com/html/html_editors.asp
        */
    }
    
    public static void yazdir(Url url){
        System.out.println("");
        if(url.derinlik == 1){
            System.out.println(url.url);
            for(Kelime kelime: url.kelimeler){
                System.out.println(kelime.kelime + ": "
                    + kelime.frekans);
            }
        }
        else if(url.derinlik == 2){
            System.out.println("\t" + url.url);
            for(Kelime kelime: url.kelimeler){
                System.out.println("\t" + kelime.kelime + ": "
                    + kelime.frekans);
            }
        }
        else if(url.derinlik == 3){
            System.out.println("\t\t" + url.url);
            for(Kelime kelime: url.kelimeler){
                System.out.println("\t\t" + kelime.kelime + ": "
                    + kelime.frekans);
            }
        }
        for(Url link: url.altUrller){
            yazdir(link);
        }
    }
}
