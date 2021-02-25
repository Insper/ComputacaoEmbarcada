const scriptURL = 'http://35.173.122.31:5000';
const sDone = 'Cheguei Aqui!'
const sReportado = 'Progresso reportado!'
const mdProgress = '---PROGRESSO---'
const htmlButton = '<button class="button0" id="0: startup" onClick="progressBut(this.id);">Cheguei Aqui!</button>'


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
    username = prompt("Ao informar o seu nome você concorda que com o uso de cookies essenciais e tecnologias semelhantes. \r\n\nCada vez que apartar o botão de progresso iremos armazenar o seu nome, o ID do botão e a hora, estes dados serão utilziados para melhor entender o comportamento dos alunos durante os estudos e aulas. \r\n\nNome completo:", "");
    if (username != "" && username != null) {
      setCookie("username", username, 365);
    } else {
      username = null;
    }
  }
  return username;
}

function setButDefauld(but) {
  but.className = "button0";
  but.firstChild.data = sDone;
}

function setButNameError(but) {
  but.firstChild.data = "Você deve aceitar os termos e preencher o seu nome para reportar progresso.";
  but.className = "button1";
  setTimeout(() => { setButDefauld(but)}, 6000);
}

function setButDone(but) {
  but.firstChild.data = sReportado;
  but.className = "button0 buttonDone";
}

function setButDoneOld(but) {
  but.firstChild.data = sReportado;
  but.className = "button0 buttonDone";
}

var url = window.location.href;
function progressBut(button_id) {
    var usrname = checkCookie();
    var but = document.getElementById(button_id);
    var text = but.firstChild;

    if (usrname != null && text.data != sReportado){
      confetti(but)
      setButDone(but);
      setCookie(url+button_id, 'true', 365);

      f = new FormData();
      f.append('name', usrname);
      f.append('time', new Date());
      f.append('id', button_id);
      f.append('url', url);
      f.append('semester', '21a');
      f.append('course', 'embarcados');
      fetch(scriptURL, { method: 'POST', body: f})
      .then(response => console.log('Success!', response))
      .catch(error => console.error('Error!', error.message));
    } else if (text.data == sReportado) {
      confetti(but)
      //pass
    }
    else {
      setButNameError(but);
    }
}


/* Coloca botao de progresso */
/*
var innerHTML = document.body.innerHTML.replace(markdown_progress, html_button);

let admonitions = document.querySelectorAll(".admonition-title");
for (var i = 0; i < admonitions.length; i++) {
    let el = admonitions[i];

    if (el.innerText == mdProgress) {

        el.innerText = en_pt[el.innerText];
    }
}*/

/* verifica estado botoes */
var buttons = document.getElementsByClassName("button0");
for ( var i = 0; i < buttons.length; i++) {
  var but = buttons[i];
  var isTrue = getCookie(url+but.id);
  if (isTrue == 'true'){
    setButDoneOld(but)
  }
}

