// Write your JavaScript code.
function UploadImageInfo(type) {
    var form = new FormData(document.getElementById("imageform"));
    form.append("ProcessType",type);
    $.ajax({
        url: "/UploadImage",
        type: "post",
        data: form,
        processData: false,
        contentType: false,
        success: function (data) {
            switch (type) {
                case 0:
                    window.location.href = data;
                    break;
                default:
                    alert("这些坑还没(人)填");
            }
        },
        error: function (e) {
        }
    });
}