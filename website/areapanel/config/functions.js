function SwitchPassword(){
    if(document.reg.pw1.disabled == true){
    	document.reg.pw1.disabled = false;
    	document.reg.pw2.disabled = false;
    }else{
    	document.reg.pw1.disabled = true;
    	document.reg.pw2.disabled = true;
    }
}
    
function UserLogin(){
	document.location = "index.php?do=login";
}

function ipn(){
    document.location = "index.php?do=ipn";
}


function CheckLoginForm() {
	if (document.login.user.value == "") {
		alert("Please enter a username");
	}else{
		if (document.login.pwd.value == ""){
			alert("Please enter a password");
		}else{
			document.login.submit;
		}
	}
}

function DisableDate(){
    if(document.ban.day.disabled == true){
    	document.ban.day.disabled = false;
    	document.ban.mes.disabled = false;
    	document.ban.year.disabled = false;
    }else{
    	document.ban.day.disabled = true;
    	document.ban.mes.disabled = true;
    	document.ban.year.disabled = true;
    }
}

function SwitchSecretQA(){
    if(document.reg.sq.disabled == true){
    	document.reg.sq.disabled = false;
    	document.reg.sa.disabled = false;
    }else{
    	document.reg.sq.disabled = true;
    	document.reg.sa.disabled = true;
    }
}

function FP_swapImgRestore() {//v1.0
 var doc=document,i; if(doc.$imgSwaps) { for(i=0;i<doc.$imgSwaps.length;i++) {
  var elm=doc.$imgSwaps[i]; if(elm) { elm.src=elm.$src; elm.$src=null; } }
  doc.$imgSwaps=null; }
}

function FP_swapImg() {//v1.0
 var doc=document,args=arguments,elm,n; doc.$imgSwaps=new Array(); for(n=2; n<args.length;
 n+=2) { elm=FP_getObjectByID(args[n]); if(elm) { doc.$imgSwaps[doc.$imgSwaps.length]=elm;
 elm.$src=elm.src; elm.src=args[n+1]; } }
}

function FP_preloadImgs() {//v1.0
 var d=document,a=arguments; if(!d.FP_imgs) d.FP_imgs=new Array();
 for(var i=0; i<a.length; i++) { d.FP_imgs[i]=new Image; d.FP_imgs[i].src=a[i]; }
}

function FP_getObjectByID(id,o) {//v1.0
 var c,el,els,f,m,n; if(!o)o=document; if(o.getElementById) el=o.getElementById(id);
 else if(o.layers) c=o.layers; else if(o.all) el=o.all[id]; if(el) return el;
 if(o.id==id || o.name==id) return o; if(o.childNodes) c=o.childNodes; if(c)
 for(n=0; n<c.length; n++) { el=FP_getObjectByID(id,c[n]); if(el) return el; }
 f=o.forms; if(f) for(n=0; n<f.length; n++) { els=f[n].elements;
 for(m=0; m<els.length; m++){ el=FP_getObjectByID(id,els[n]); if(el) return el; } }
 return null;
}

function cambio(idCapa){
 if (document.layers) capa = eval("document." + idCapa);
 if (document.all) capa = eval(idCapa + ".style");
 if (document.getElementById) capa = eval('document.getElementById("' + idCapa + '").style');

 if ((capa.visibility == "hidden") || (capa.visibility == "hide")){
  capa.visibility = (document.layers) ? "show" : "visible" ;
 }else{
  capa.visibility = (document.layers) ? "hide" : "hidden" ;
 }
}

function CheckUserID(){
	if (document.pwd.userid.value == ""){
		alert('Please enter a User ID!');
	}else{
		document.pwd.submit;
	}
}

function UpdateCustom(){
	if(document.ban.reason.value == 1){
		document.ban.cstom.disabled = false;
	}else{
		document.ban.cstom.disabled = true;
	}
}


    function SwitchItem(){
    	document.location = "index.php?do=rzitemshop&sub=listallitems&expand=1&type=" + document.itemtype.type.value;
    }

    function SwitchItem2(){
    	document.location = "index.php?do=evitemshop&sub=listallitems&expand=1&type=" + document.itemtype.type.value;
    }