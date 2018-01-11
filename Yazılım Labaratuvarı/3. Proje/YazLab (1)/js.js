$(function(){
	/*****AŞAMA 1*****/
	$("#ara1").click(function(){
		var url = $("#url1").val();
		var str = $("#str1").val();
		$.post("php.php", {'asama': '1', 'url': url, 'str': str}, function(veri){
			$("#sonuc1").text(veri);
		});
	});

	/*****AŞAMA 2*****/
	var url2sayisi = 1;
	$("#ekle2").click(function(){
		url2sayisi++;
		var kontrol = "#url2-" + (url2sayisi - 1);
		if($(kontrol).val() != ""){
			$("#asama2").prepend("<input id='url2-" + url2sayisi + "' type='text' style='width: 100%;'>");
		}
		else{
			url2sayisi--;
		}
	});

	$("#ara2").click(function(){
		var i;
		var urller = [];
		var url;
		var id;
		for(i = 1; i <= url2sayisi; i++){
			id = "#url2-"+i;
			url = $(id).val();
			urller.push(url);
		}

		var str2 = $("#str2").val();
		var kelimeler = str2.split(" ");

		arama(urller, kelimeler, 2);
	});

	/*****AŞAMA 3*****/
	var url3sayisi = 1;
	$("#ekle3").click(function(){
		url3sayisi++;
		var kontrol = "#url3-" + (url3sayisi - 1);
		if($(kontrol).val() != ""){
			$("#asama3").prepend("<input id='url3-" + url3sayisi + "' type='text' style='width: 100%;'>");
		}
		else{
			url3sayisi--;
		}
	});

	$("#ara3").click(function(){
		var i, j, k;
		var urller = [];
		var url;
		var id;
		for(i = 1; i <= url3sayisi; i++){
			id = "#url3-"+i;
			url = $(id).val();
			urller.push(url);
		}

		var str3 = $("#str3").val();
		var kelimeler = str3.split(" ");

		arama(urller, kelimeler, 3);
	});


	
	





	function arama(urller, kelimeler, asama){
		$.post("php.php", {'asama': asama, 'urller': urller, 'kelimeler': kelimeler}, function(veri){
			var tbody = "#tbody" + asama;
			veri = veri.split(" ");
			var verisayisi = veri.length - 1;
			var kelimesayisi = kelimeler.length;
			var str;
			for(var i = 0; i < verisayisi - 2; i += ((2*kelimesayisi) + 2)){
				str = "<tr><td>" + veri[i] + "</td><td>" + veri[i+1] + "</td><td>";
				for(var j = 0; j < 2*kelimesayisi; j+=2){
					str += veri[i+2+j] + ": " + veri[i+2+j+1];
					if((j+3) < 2*kelimesayisi){
						str += "<br>";
					}
				}
				str += "</td></tr>";
				$(tbody).append(str);
			}
			alert("bitti");
		});
	}








});