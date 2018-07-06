using Microsoft.AspNetCore.Http;
using System.ComponentModel.DataAnnotations;

namespace WebImage2Text.Models
{
    public class ImageViewModel
    {

        [Range(1, int.MaxValue)]
        public int ScaleX { get; set; }
        [Range(1, int.MaxValue)]
        public int ScaleY { get; set; }
        public string UploadedFileName { get; set; }
        [Required]
        [Display(Name = "Image to upload")]
        [FileExtensions(Extensions = ".jpg,.png,.bmp", ErrorMessage = "Error image format.")]
        public IFormFile SourceImage { get; set; }
    }
    public class AppSettings
    {
        public string ExecuteFileName { get; set; }
    }
}
