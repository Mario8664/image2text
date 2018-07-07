// Write your JavaScript code.
function UploadImageInfo(type) {
    var form = new FormData(document.getElementById("imageform"));
    form.append("ProcessType", type);
    for (var value of form.values()) {
        if (value == "") return false;
    }
    $.ajax({
        url: "/UploadImage",
        type: "post",
        data: form,
        processData: false,
        contentType: false,
        success: function (data) {
            switch (type) {
                case 0:
                    window.location.href = "Home/ShowCharGraphHtml";
                    break;
                case 2:
                    window.location.href = "Home/DownloadText";
                    break;
                default:
                    alert("这些坑还没填");
            }
        },
        error: function (e) {

        }
    });
}