namespace PlatformEditor
{
    partial class AutoTile
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AutoTile));
            this.AutoTileSelect = new System.Windows.Forms.PictureBox();
            this.TilesetImage = new System.Windows.Forms.PictureBox();
            this.SelectedAutoTilesImage = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.AutoTileSelect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TilesetImage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SelectedAutoTilesImage)).BeginInit();
            this.SuspendLayout();
            // 
            // AutoTileSelect
            // 
            this.AutoTileSelect.Image = ((System.Drawing.Image)(resources.GetObject("AutoTileSelect.Image")));
            this.AutoTileSelect.Location = new System.Drawing.Point(12, 12);
            this.AutoTileSelect.Name = "AutoTileSelect";
            this.AutoTileSelect.Size = new System.Drawing.Size(798, 50);
            this.AutoTileSelect.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.AutoTileSelect.TabIndex = 0;
            this.AutoTileSelect.TabStop = false;
            this.AutoTileSelect.Click += new System.EventHandler(this.AutoTileSelect_Click);
            this.AutoTileSelect.Paint += new System.Windows.Forms.PaintEventHandler(this.AutoTileSelect_Paint);
            this.AutoTileSelect.MouseDown += new System.Windows.Forms.MouseEventHandler(this.AutoTileSelect_Click);
            // 
            // TilesetImage
            // 
            this.TilesetImage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TilesetImage.Location = new System.Drawing.Point(12, 224);
            this.TilesetImage.Name = "TilesetImage";
            this.TilesetImage.Size = new System.Drawing.Size(100, 50);
            this.TilesetImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.TilesetImage.TabIndex = 1;
            this.TilesetImage.TabStop = false;
            this.TilesetImage.Click += new System.EventHandler(this.TilesetImage_Click);
            this.TilesetImage.Paint += new System.Windows.Forms.PaintEventHandler(this.TilesetImage_Paint);
            this.TilesetImage.MouseMove += new System.Windows.Forms.MouseEventHandler(this.TilesetImage_MouseMove);
            // 
            // SelectedAutoTilesImage
            // 
            this.SelectedAutoTilesImage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.SelectedAutoTilesImage.Location = new System.Drawing.Point(12, 68);
            this.SelectedAutoTilesImage.Name = "SelectedAutoTilesImage";
            this.SelectedAutoTilesImage.Size = new System.Drawing.Size(800, 150);
            this.SelectedAutoTilesImage.TabIndex = 2;
            this.SelectedAutoTilesImage.TabStop = false;
            this.SelectedAutoTilesImage.Paint += new System.Windows.Forms.PaintEventHandler(this.SelectedAutoTilesImage_Paint);
            this.SelectedAutoTilesImage.MouseDown += new System.Windows.Forms.MouseEventHandler(this.SelectedAutoTilesImage_MouseDown);
            this.SelectedAutoTilesImage.MouseLeave += new System.EventHandler(this.SelectedAutoTilesImage_MouseLeave);
            this.SelectedAutoTilesImage.MouseMove += new System.Windows.Forms.MouseEventHandler(this.SelectedAutoTilesImage_MouseMove);
            // 
            // AutoTile
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(823, 599);
            this.Controls.Add(this.SelectedAutoTilesImage);
            this.Controls.Add(this.TilesetImage);
            this.Controls.Add(this.AutoTileSelect);
            this.Name = "AutoTile";
            this.Text = "AutoTile";
            this.Load += new System.EventHandler(this.AutoTile_Load);
            ((System.ComponentModel.ISupportInitialize)(this.AutoTileSelect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TilesetImage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SelectedAutoTilesImage)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox AutoTileSelect;
        private System.Windows.Forms.PictureBox TilesetImage;
        private System.Windows.Forms.PictureBox SelectedAutoTilesImage;
    }
}