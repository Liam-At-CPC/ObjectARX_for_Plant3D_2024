// adsk.common.js - JavaScript functions for ACAD Help Files

// v.1.0: 25Feb09 - Removed unneccessary code. moved common code from acmap.js
//                  Contains all JavaScript functions used by CMS-genereated HTML files 
//                  for the CHM output.

//TODO: Add Browser Detection code and global variable (if neccessary)
var isIE = false;
var isNS = false;
if (navigator.appName == "Microsoft Internet Explorer") {
    isIE = true;
}
else if (navigator.appName == "Netscape") {
    isNS = true;
}

//Global Method for attaching methods to the OnLoad event
// All other JS files should call AddOnLoadFunction
function AddOnLoadFunction(fn) {
    try {
        if (window.attachEvent) {
            window.attachEvent('onload', fn);
        } else if (window.addEventListener) {
            window.addEventListener('load', fn, false);
        } else {
            var __onload = window.onload;
            window.onload = function() {
                fn();
                __onload();
            };
        }
    } catch (e) {

    }
}

//Display the comments page
function doComments(path) {
  
  var stitle = document.title;
  stitle = stitle.replace( /[\?]/g, "_" );  // remove question marks from title (others?)
  
  var surl   = unescape(location.href);
  surl = surl.replace( /#.*$/, "" );  // strip hash and all that follows

  var chmpath;
  var i = surl.indexOf("::");
  if( i == -1 ) {
    i = surl.lastIndexOf("/"); 
    chmpath = surl.substring(0,i+1);
  } else {
    chmpath = surl.substring(0,i+3);
  }
  //Display a fixed height window with none of the browser chrome
  window.open(chmpath + path + "#" + stitle + " [" + surl + "]", null,
              "height=450,width=450,resizable=yes,directories=no,location=no,menubar=no,status=no,toolbar=no" );
}

// Display/Hide nav button info text
function hideInfo() {
    var info = document.getElementById('infoline');
    info.innerHTML = ' ';
    info.style.visibility = 'hidden';
}

function showInfo(title) {
    var info = document.getElementById('infoline');
    info.innerHTML = title;
    info.style.visibility = 'visible';
}

//-------------------------------------------
// Added by IntelliArts
//-------------------------------------------

// Trim polyfill.
if (!String.prototype.trim) {
  String.prototype.trim = function () {
    return this.replace(/^\s+|\s+$/g, '');
  };
}

function trimRelativePath(path) {
    if (path.indexOf('./') === 0) {
        return trimRelativePath(path.substring(2));
    } else if (path.indexOf('../') === 0) {
        return trimRelativePath(path.substring(3));
    } else if (path.indexOf('../') > 0) {
        if (path.indexOf('/') < path.indexOf('../')) {
            return trimRelativePath(path.substring(0, path.indexOf('/')) + path.substring(path.indexOf('../') + 3));
        } else {
            return path;
        }
    } else {
        return path;
    }
}

function swapImage(theImgObj, theImage1, theImage2) {
    if (theImgObj.src.search(trimRelativePath(theImage1)) > 0 || theImage1 == theImgObj.src) {
        theImgObj.src = theImage2;
    } else {
        theImgObj.src = theImage1;
    }
}

function showExpandedImage(theImgObj, theImage) {
    if (theImgObj.src != theImage) {
        theImgObj.src = theImage;
    }
}

function hideElement(theEl) {
    addClass(theEl, 'hidden');
}

function showElement(theEl) {
    removeClass(theEl, 'hidden');
}

function showHide(theId) {
    if (document.getElementById) { // DOM3 = IE5, NS6
        var el = document.getElementById(theId);

        if (el === null) {
            return;
        }

        var theElClass = ' ' + el.className + ' ';

        if (theElClass.indexOf(' hidden ') != -1) {
            showElement(el);
        } else {
            hideElement(el);
        }
    }
}

function addClass(theEl, className) {
    theEl.className = theEl.className.trim() + ' ' + className;
}

function removeClass(theEl, className) {
    var theElClass = ' ' + theEl.className + ' ';

    while (theElClass.indexOf(' ' + className + ' ') != -1) {
        theElClass = theElClass.replace(' ' + className + ' ' , '');
    }

    theEl.className = theElClass.trim();
}

function showBlock(theId) {
    if (document.getElementById) { // DOM3 = IE5, NS6
        var el = document.getElementById(theId);
        if (el === null) {
            return ;
        }
        if (el.style.display == 'none') {
            showElement(el);
        }
    }
}

// Used for External Links
function linkParser(fn) {
    var X, Y, sl, a, ra;
    ra = /:/;
    a = location.href.search(ra);
    if (a == 2) {
        X = 14;
    } else {
        X = 7;
    }
    sl = "\\";
    Y = location.href.lastIndexOf(sl) + 1;
    var tmpRes = location.href.substring(X, Y) + fn;
    if (!(location.href.search('file:///') >= 0)) {
        tmpRes = 'file:///' + tmpRes;
    }
    return tmpRes;
}

//Used for External Links
function linkHelpFile(fn, tn) {
    var fileUrl = linkParser(fn);
    var tmpRes = 'mk:@MSITStore:' + fileUrl;
    if (tn !== null) {
        tmpRes += '::/' + tn;
    }
    return tmpRes;
}

//-------------------------------------------
//ExpandAll CollapseAll scripts
/* essential global variables */
var divPattern;
var els;
var elsLen;
var collapseExists = false;
var collapseSection;
var expandSection;
var collapsedImagePath;
var expandedImagePath;

function CheckForCollapsible() {

    divPattern = new RegExp(/collapsible\w+/);
    els = document.getElementsByTagName('div');
    elsLen = els.length;
    collapseSection = document.getElementById("collapseAllSection");
    expandSection = document.getElementById("expandAllSection");

    var i = 0;
    while (i < elsLen && !collapseExists) {
        if (divPattern.test(els[i].getAttribute("id"))) {
            collapseExists = true;
        }
        i++;
    }

    if (collapseExists && expandSection !== null) {
        expandSection.style.display = "block";
        try {
            collapsedImagePath = document.getElementById("collapse_img").src;
            expandedImagePath = document.getElementById("expand_img").src;
        } catch (e) {
        }
    }

}   // function CheckForCollapsible()

// Add CheckForCollapsible to OnLoad
AddOnLoadFunction(CheckForCollapsible);


function swapLabel() {
    if (collapseSection.style.display == "block") {
        collapseSection.style.display = "none";
        expandSection.style.display = "block";
    } else {
        collapseSection.style.display = "block";
        expandSection.style.display = "none";
    }
}

function ExpandOrCollapse() {

    var imgPattern = new RegExp(/d\w+/);
    var imgID = document.getElementsByTagName('img');
    var imgIDLen = imgID.length;
        
    for (var i = 0; i < elsLen; i++) {
        var elsId = els[i].getAttribute("id")
        if (divPattern.test(elsId)) {
            showHide(elsId);
        }
    }

    for (var j = 0; j < imgIDLen; j++) {
        if (imgPattern.test(imgID[j].getAttribute("id"))) {
            swapImage(imgID[j], expandedImagePath, collapsedImagePath);
        }
    }

    swapLabel();
}

function ExpandAll() {

    var imgPattern = new RegExp(/d\w+/);
    var imgID = document.getElementsByTagName('img');
    var imgIDLen = imgID.length;
    var elID;

    for (var i = 0; i < elsLen; i++) {
        if (divPattern.test(els[i].getAttribute("id"))) {
            elID = els[i].getAttribute("id");
            showBlock(elID);
        }
    }

    for (var j = 0; j < imgIDLen; j++) {
        if (imgPattern.test(imgID[j].getAttribute("id"))) {
            showExpandedImage(imgID[j], expandedImagePath);
        }
    }

    swapLabel();
}

function CollapseAll() {

    window.location.reload();

}
