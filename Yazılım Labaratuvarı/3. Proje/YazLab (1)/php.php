<?php
	
	set_time_limit(0);

	$urller = [];
	$kelimeler = [];
	$sonuc = [[]];
	$puan = [];

	$asama = $_POST['asama'];

	switch ($asama) {
		case '1':
			asama1();
			break;
		case '2':
			asama2();
			break;
		case '3':
			asama3();
			break;
		case '4':
			# code...
			break;
	}

	function asama1()
	{
		$url = $_POST['url'];
		$kelime = $_POST['str'];
		$veri = file_get_contents($url);
		$frekans = kelime_frekansi_hesapla($veri, $kelime);
		echo $frekans;
	}

	function asama2()
	{
		global $urller, $kelimeler;

		$kelimeler = $_POST['kelimeler'];
		$urller = $_POST['urller'];

		arama();
		site_siralama();
		$str = stringe_al();
		echo $str;
	}

	function asama3()
	{
		global $urller, $kelimeler;

		$kelimeler = $_POST['kelimeler'];
		$urller = $_POST['urller'];

		$altlinkler1 = linkleri_al($urller);
		$urller = array_merge($urller, $altlinkler1);
		$altlinkler2 = linkleri_al($altlinkler1);
		$urller = array_merge($urller, $altlinkler1, $altlinkler2);

		/*$str = stringle($urller);
		echo $str;*/

		arama();
		site_siralama();
		$str = stringe_al();
		echo $str;
	}















	function linkleri_al($urller)
	{
		$altlinkler = [];
		for($i = 0; $i < count($urller); $i++) {
			$veri = @file_get_contents($urller[$i]);
			preg_match_all("/href=\"([^\"]+)/i", $veri, $linkler);
			foreach ($linkler[1] as $link){
				if(strstr($link, "http") !== false){
					array_push($altlinkler, $link);
				}
			}
		}
		return $altlinkler;
	}

	function stringle($linkler)
	{
		$str = "";
		foreach ($linkler as $link) {
			$str .= $link." ";
		}
		return $str;
	}

	function arama()
	{
		global $urller, $puan, $sonuc, $kelimeler;
		$sinir1 = count($urller);
		$sinir2 = count($kelimeler);

		for($i = 0; $i < $sinir1; $i++){
			$veri = @file_get_contents($urller[$i]);
			for($j = 0; $j < $sinir2; $j++){
				$sonuc[$i][$j] = kelime_frekansi_hesapla($veri, $kelimeler[$j]);
			}
			$puan[$i] = puanlama($sonuc[$i], $kelimeler);
		}
	}

	function kelime_frekansi_hesapla($veri, $kelime){
		$frekans = 0;
		$position = 0;
		do{
			$position = stripos($veri, $kelime, $position+1);
			$frekans++;
		}while($position !== false);
		$frekans--;
		return $frekans;
	}

	function puanlama($sonuc, $kelimeler){
		$sayi = count($kelimeler);
		$toplam = 0;
		for($i = 0; $i < $sayi; $i++){
			$toplam += $sonuc[$i];
		}
		return round($toplam/$sayi);
	}

	function site_siralama(){
		global $urller, $puan, $sonuc;
		$sinir = count($puan);
		for($i=0; $i < $sinir; $i++){
			for($j=0; $j<$sinir-$i-1; $j++){
				if($puan[$j] < $puan[$j+1]){
					$gecici1 = $puan[$j];
					$puan[$j] = $puan[$j+1];
					$puan[$j+1] = $gecici1;

					$gecici2 = $urller[$j];
					$urller[$j] = $urller[$j+1];
					$urller[$j+1] = $gecici2;

					$gecici3 = $sonuc[$j];
					$sonuc[$j] = $sonuc[$j+1];
					$sonuc[$j+1] = $gecici3;
				}
			}
		}
	}

	function stringe_al(){
		global $urller, $puan, $sonuc, $kelimeler;
		$sinir1 = count($sonuc);
		$sinir2 = count($sonuc[0]);
		$str = "";

		for($i = 0; $i < $sinir1; $i++){
			$str .= $urller[$i]." ".$puan[$i]." ";
			for($j = 0; $j < $sinir2; $j++){
				$str .= $kelimeler[$j]." ".$sonuc[$i][$j]." ";
			}
		}
		return $str;
	}

?>