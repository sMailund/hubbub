var http = require('http'); //importer http
var fs = require('fs');

var config = require('./config');

const PORT = config.port; //sett port
const IP = config.ip; //set ip

var isCalled = false;

function handleRequest(request, response){
    console.log("got request: " + request.url + request.method);
    
    switch(request.url) {
	case '/':
	    response.end();
	    break;
        case '/call': 
            isCalled = true;
            console.log('isCalled = ' + isCalled);
	    response.end();
            break;
        case '/reset': 
            isCalled = false;
            console.log('isCalled = ' + isCalled);
	    response.end();
            break;
        case '/status': 
            response.write(isCalled ? '1' : '0');
	    response.end();
            break;
	case '/controller':
	    response.writeHead(200, {"Content-Type": "text/html"});
	    fs.createReadStream("./kontroll.html").pipe(response);
	    break;
	case '/paa':
	    isCalled = true;
	    response.end();
	    break;
	case '/av':
	    isCalled = false;
	    response.end();
	    break;
	default:
	    response.statusCode = 404;
	    response.write("404 not found");
	    response.end();
    }
}

var server = http.createServer(handleRequest);

server.listen(PORT, IP, function(){
    console.log("Server listening on: http://%s:%s", IP, PORT);
});
