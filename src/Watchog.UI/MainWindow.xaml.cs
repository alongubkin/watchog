using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Watchog.Persistence.Models;

namespace Watchog.UI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly TaskScheduler _uiTaskScheduler;

        public MainWindow()
        {
            InitializeComponent();

            _uiTaskScheduler = TaskScheduler.FromCurrentSynchronizationContext();

            ((App)Application.Current).PersistenceContext.MoviesUpdated += UpdateMovies;
            UpdateMovies();
        }

        private void UpdateMovies()
        {
            ((App)Application.Current).PersistenceContext.Database.GetRecentlyWatched(0)
                .ContinueWith((task) =>
                {
                    MoviesListView.ItemsSource = task.Result;
                    MoviesListView.Items.Refresh();
                }, _uiTaskScheduler);
        }

        private void TitleBar_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            DragMove();
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            Hide();
        }

        private void MinimizeButton_Click(object sender, RoutedEventArgs e)
        {
            WindowState = WindowState.Minimized;
        }
    }
}
