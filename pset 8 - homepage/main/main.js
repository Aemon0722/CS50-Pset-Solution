document.addEventListener("DOMContentLoaded", function (){
    reduceImgHeight();
})

function reduceImgHeight(){
    let boxes = document.querySelectorAll("main img");
    boxes.forEach(function(box){
        let width = box.offsetWidth;
        if(width < 400){
            box.style.height = width + "px";
        }
    });
}

let mql = window.matchMedia("(min-width: 1000px)");

mql.addListener(function(e){
    if(e.matches){
        reduceImgHeight();
    }
})
