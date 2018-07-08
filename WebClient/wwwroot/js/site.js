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
                    window.location.href = "/ShowCharGraphHtml";
                    break;
                case 2:
                    window.location.href = "/DownloadText";
                    break;
                case 1:
                    window.location.href = "/ShowColorHtml";
                    break;
                default:
                    alert("Unexpected Error.");
                    break;
            }
        },
        error: function (e) {

        }
    });
}