let en_pt = {
    "Note": "Nota",
    "Tip": "Dica",
    "Question": "Pergunta",
    "Warning": "Atenção!",
    "Example": "Exemplo"
};

let admonitions_to_translate = document.querySelectorAll(".admonition-title");

for (var i = 0; i < admonitions_to_translate.length; i++) {
    let el = admonitions_to_translate[i];

    if (el.innerText in en_pt) {
        el.innerText = en_pt[el.innerText];
    }
}

document.body.innerHTML = document.body.innerHTML.replace( /\\newpage/g, "");
