const scriptURL = 'https://script.google.com/macros/s/AKfycbxJTJIvfkJzTusu8PGkyP1aGmA7KSrKq8H4OiiQYSl9Lf6ZVM8/exec';

function setCookie(cname, cvalue, exdays) {
  var d = new Date();
  d.setTime(d.getTime() + (exdays*24*60*60*1000));
  var expires = "expires="+ d.toUTCString();
  document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}

function getCookie(cname) {
  var name = cname + "=";
  var decodedCookie = decodeURIComponent(document.cookie);
  var ca = decodedCookie.split(';');
  for(var i = 0; i <ca.length; i++) {
    var c = ca[i];
    while (c.charAt(0) == ' ') {
      c = c.substring(1);
    }
    if (c.indexOf(name) == 0) {
      return c.substring(name.length, c.length);
    }
  }
  return "";
}

function checkCookie() {
  var username = getCookie("username");
  if (username == "") {
    username = prompt("Informe seu nome completo:", "");
    if (username != "" && username != null) {
      setCookie("username", username, 365);
    }
  }
  return username;
}

function setButDefauld(but) {
  but.className = "button0";
  but.firstChild.data = "Cheguei Aqui!";
}

function setButNameError(but) {
  but.firstChild.data = "Preencha o nome antes de seguir.";
  but.className = "button1";
  setTimeout(() => { setButDefauld(but)}, 2000);
}

function setButDone(but) {
  but.firstChild.data = "Progresso reportado!";
  but.className = "button0 buttonDone";
}

function setButDoneOld(but) {
  but.firstChild.data = "Progresso já reportado!";
  but.className = "button0 buttonDone";
}

var url = window.location.href;
var usrname = checkCookie();

function progressBut(button_id) {
    var but = document.getElementById(button_id);
    var text = but.firstChild;
    if (usrname != "" && text.data == "Cheguei Aqui!"){
      setButDone(but);
      setCookie(url+button_id, 'true', 365);

      f = new FormData();
      f.append('name', usrname);
      f.append('time', new Date());
      f.append('id', button_id);
      f.append('url', url);
      fetch(scriptURL, { method: 'POST', body: f})
      .then(response => console.log('Success!', response))
      .catch(error => console.error('Error!', error.message));
    } else {
      setButNameError(but);
    }
}

var buttons = document.getElementsByClassName( "button0");

for ( var i = 0; i < buttons.length; i++) {
  var but = buttons[i];
  var isTrue = getCookie(url+but.id);
  if (isTrue == 'true'){
    setButDoneOld(but)
  }
}
