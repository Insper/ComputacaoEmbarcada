// If the element's string matches the regular expression it is all numbers
function isNumeric(elem, helperMsg){
	  var numericExpression = /^[0-9]+$/;
	  if(elem.value.match(numericExpression)){
		    return true;
	  }else{
		    alert(helperMsg);
		    elem.focus();
		    return false;
	  }
}

function checkBeforeSubmit(){
	  if ((isNumeric(document.getElementById('numbers'), 'Please enter a number'))){
		    document.getElementById('theForm').submit();
		    document.getElementById('success').innerHTML='Submitted';
	  }
}
