document.addEventListener("DOMContentLoaded", function (){
    showSidebar();
    closeSidebar();
})

// show the sidebar when clicking the menu icon only for mobile view
function showSidebar(){
    const sidebar = document.querySelector(".sidebar");
    sidebar.style.display = "flex";
}

// close the sidebar when clicking the close menu icon
function closeSidebar(){
    const close = document.querySelector(".sidebar");
    close.style.display = "none";
}
