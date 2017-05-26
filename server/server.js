var http = require('http'); //importer http
var fs = require('fs'); //importer filsystem

var config = require('./config'); //hent konfigurasjonsfil

const PORT = config.port; //sett port
const IP = config.ip; //set ip

var isCalled = false; //denne endres hvis bussen er tilkalt

//kalles naar en foresporsel er registrert
function handleRequest(request, response){
    console.log("got request: " + request.url + request.method);
	
    //behandle foresporsel
    switch(request.url) {
	case '/':
	    response.end();
	    break;
        case '/call':
	    //bussen er tilkalt, sett isCalled
            isCalled = true;
            console.log('isCalled = ' + isCalled);
	    response.end();
            break;
        case '/reset':
            //bussen er avbestilt, sett isCalled
            isCalled = false;
            console.log('isCalled = ' + isCalled);
	    response.end();
            break;
        case '/status': 
            response.write(isCalled ? '1' : '0'); //svarer tilbake med status
	    response.end();
            break;
	case '/controller':
            //send kontrollpanel tilbake til nettleser, hovedsakelig for debug
	    response.writeHead(200, {"Content-Type": "text/html"});
	    fs.createReadStream("./kontroll.html").pipe(response);
	    break;
	case '/paa':
            //bestilling fra kontrollpanel paa web, brukes til debug
	    isCalled = true;
	    response.end();
	    break;
	case '/av':
	    //avbestilling fra kontrollpanel paa web, brukes til debug
	    isCalled = false;
	    response.end();
	    break;
	default:
	    //404 not found
	    response.statusCode = 404;
	    response.write("404 not found");
	    response.end();
    }
}

var server = http.createServer(handleRequest); //start server

//lytt til port
server.listen(PORT, IP, function(){
    console.log("Server listening on: http://%s:%s", IP, PORT);
});
