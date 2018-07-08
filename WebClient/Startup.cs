using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using WebImage2Text.Models;

namespace WebImage2Text
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddMvc();
            services.AddOptions();
            services.Configure<AppSettings>(Configuration.GetSection("AppSettings"));
            services.AddSession();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IHostingEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseBrowserLink();
                app.UseDeveloperExceptionPage();
            }
            else
            {
                app.UseExceptionHandler("/Home/Image2Text");
                
            }
            app.UseStaticFiles();
            app.UseSession();
            app.UseMvc(routes =>
            {
                routes.MapRoute(
                    "CharGraphResult",
                    "ShowCharGraphHtml/",
                    new { controller = "Home",action= "ShowCharGraphHtml" }
                    );
                routes.MapRoute(
                    "DownloadText",
                    "DownloadText/",
                    new { controller = "Home", action = "DownloadText" }
                    );
                routes.MapRoute(
                    "ShowColorHtml",
                    "ShowColorHtml/",
                    new { controller = "Home", action = "ShowColorHtml" }
                    );
                routes.MapRoute(
                    "Default",
                     "{controller}/{action}",
                     new { controller = "Home", action = "Image2Text" }
                     );
                routes.MapRoute(
                    "ErrorPage",
                    "Error/{id?}/{Content?}",
                    new { controller = "Home" ,action= "Error" }
                    );
            });
        }
    }
}
