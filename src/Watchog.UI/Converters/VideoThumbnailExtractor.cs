using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media.Imaging;
using NReco.VideoConverter;

namespace Watchog.UI.Converters
{
    public sealed class VideoThumbnailExtractor : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var path = value as string;
            if (path == null)
            {
                return null;
            }

            var image = new BitmapImage();
            image.BeginInit();
            image.CacheOption = BitmapCacheOption.OnLoad;

            using (var imageStream = new MemoryStream())
            {
                new FFMpegConverter().GetVideoThumbnail(value.ToString(), imageStream, 100);
                imageStream.Seek(0, SeekOrigin.Begin);
                image.StreamSource = imageStream;
                image.EndInit();
            }

            
            return image;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }
}
