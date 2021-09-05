using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PlatformEditor
{

    public partial class AutoTile : Form
    {
        private int mySelectedAutoTile = 0;
        private int mySelectedTilsetTile = 0;
        private int myTileToRemove = -1;
        private Tileset myTileSet = null;

        public AutoTile(Tileset aTileset)
        {
            InitializeComponent();
            myTileSet = aTileset;
            TilesetImage.Image = myTileSet.GetImage();
        }

        private void AutoTile_Load(object sender, EventArgs e)
        {

        }

        private void AutoTileSelect_Click(object sender, EventArgs e)
        {
            MouseEventArgs mouseEvents = (MouseEventArgs)e;
            mySelectedAutoTile = (int)(mouseEvents.X / 50);
            AutoTileSelect.Refresh();
        }

        private void AutoTileSelect_Paint(object sender, PaintEventArgs e)
        {
            Pen pen = new Pen(Color.YellowGreen, 2);
            e.Graphics.DrawRectangle(pen, new Rectangle(mySelectedAutoTile * 50, 0, 50, 50));
        }

        private void TilesetImage_MouseMove(object sender, MouseEventArgs e)
        {
            mySelectedTilsetTile = (e.X / myTileSet.TileWidth) +
                (e.Y / myTileSet.TileHeight) * myTileSet.GetTileCols();
            TilesetImage.Refresh();
        }

        private void TilesetImage_Paint(object sender, PaintEventArgs e)
        {
            int x = mySelectedTilsetTile % myTileSet.GetTileCols() * myTileSet.TileWidth;
            int y = mySelectedTilsetTile / myTileSet.GetTileCols() * myTileSet.TileHeight;
            Pen pen = new Pen(Color.Cyan);
            pen.Width = 2;
            e.Graphics.DrawRectangle(pen, x, y, myTileSet.TileWidth, myTileSet.TileHeight);
        }

        private void TilesetImage_Click(object sender, EventArgs e)
        {
            if (myTileSet.myAutoTiles[mySelectedAutoTile].Contains(mySelectedTilsetTile) == false)
            {
                myTileSet.myAutoTiles[mySelectedAutoTile].Add(mySelectedTilsetTile);
            }
            SelectedAutoTilesImage.Refresh();
        }

        private void SelectedAutoTilesImage_Paint(object sender, PaintEventArgs e)
        {
            for (int autoTileIndex = 0; autoTileIndex < myTileSet.myAutoTiles.Length; autoTileIndex++)
            {
                for (int selectedTileIndex = 0; selectedTileIndex < myTileSet.myAutoTiles[autoTileIndex].Count; selectedTileIndex++)
                {
                    int x = autoTileIndex * 50;
                    int y = selectedTileIndex * 50;
                    int xSrc = myTileSet.myAutoTiles[autoTileIndex][selectedTileIndex] % myTileSet.GetTileCols() * myTileSet.TileWidth;
                    int ySrc = myTileSet.myAutoTiles[autoTileIndex][selectedTileIndex] / myTileSet.GetTileCols() * myTileSet.TileHeight;
                    Rectangle dst = new Rectangle(x, y, 50, 50);
                    Rectangle src = new Rectangle(xSrc, ySrc, myTileSet.TileWidth, myTileSet.TileHeight);
                    e.Graphics.DrawImage(myTileSet.GetImage(), dst, src, GraphicsUnit.Pixel);
                }
            }

            if (myTileToRemove != -1)
            {
                int selectionX = (myTileToRemove % 16) * 50;
                int selectionY = (myTileToRemove / 16) * 50;
                Pen pen = new Pen(Color.Red);
                pen.Width = 2;
                e.Graphics.DrawRectangle(pen, selectionX, selectionY, 50, 50);
            }
        }

        private void AutoTileSelect_Click(object sender, MouseEventArgs e)
        {

        }

        private void SelectedAutoTilesImage_MouseDown(object sender, MouseEventArgs e)
        {
            int autoTileIndex = e.X / 50;
            int index = e.Y / 50;

            if (index < myTileSet.myAutoTiles[autoTileIndex].Count)
            {
                myTileSet.myAutoTiles[autoTileIndex].RemoveAt(index);
            }

            SelectedAutoTilesImage.Refresh();
        }

        private void SelectedAutoTilesImage_MouseMove(object sender, MouseEventArgs e)
        {
            myTileToRemove = (e.X / 50) + (e.Y / 50) * 16;
            SelectedAutoTilesImage.Refresh();
        }

        private void SelectedAutoTilesImage_MouseLeave(object sender, EventArgs e)
        {
            myTileToRemove = -1;
            SelectedAutoTilesImage.Refresh();
        }
    }
}
