using Microsoft.AspNetCore.Http;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace WebImage2Text.Models
{
    public class ImageViewModel
    {
        [Required]
        [Range(1, int.MaxValue)]
        public int ScaleX { get; set; }
        [Required]
        [Range(1, int.MaxValue)]
        public int ScaleY { get; set; }
        public string UploadedFileName { get; set; }
        [Required]
        [Display(Name = "Image to upload")]
        [FileExtensions(Extensions = ".jpg,.png,.bmp", ErrorMessage = "Error image format.")]
        public List<IFormFile> SourceImage { get; set; }
        public string CharGraphResult { get; set; }
    }
    public class AppSettings
    {
        public string ExecuteFileName { get; set; }
        public string ImageUploadPath { get; set; }
        public string TextFileSavaPath { get; set; }
    }
}
