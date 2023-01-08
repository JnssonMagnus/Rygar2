namespace PlatformEditor
{
    partial class TilesetEditor
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
            this.TilesetImage = new System.Windows.Forms.PictureBox();
            this.TileWidth = new System.Windows.Forms.NumericUpDown();
            this.TileHeight = new System.Windows.Forms.NumericUpDown();
            this.ObstacleCheckbox = new System.Windows.Forms.CheckBox();
            this.SelectTilesetTexture = new System.Windows.Forms.Button();
            this.TilesetFilenameText = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.Tilesets = new System.Windows.Forms.ComboBox();
            this.AddTilesetButton = new System.Windows.Forms.Button();
            this.RemoveTilesetButton = new System.Windows.Forms.Button();
            this.SaveButton = new System.Windows.Forms.Button();
            this.DestructableCheckbox = new System.Windows.Forms.CheckBox();
            this.AutoTileBtn = new System.Windows.Forms.Button();
            this.FalloutCheckBox = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.TilesetImage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TileWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TileHeight)).BeginInit();
            this.SuspendLayout();
            // 
            // TilesetImage
            // 
            this.TilesetImage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TilesetImage.Location = new System.Drawing.Point(540, 38);
            this.TilesetImage.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TilesetImage.Name = "TilesetImage";
            this.TilesetImage.Size = new System.Drawing.Size(347, 300);
            this.TilesetImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.TilesetImage.TabIndex = 0;
            this.TilesetImage.TabStop = false;
            this.TilesetImage.Click += new System.EventHandler(this.TilesetImage_Click);
            this.TilesetImage.Paint += new System.Windows.Forms.PaintEventHandler(this.TilesetImage_Paint);
            this.TilesetImage.MouseMove += new System.Windows.Forms.MouseEventHandler(this.TilesetImage_MouseMove);
            // 
            // TileWidth
            // 
            this.TileWidth.Location = new System.Drawing.Point(92, 38);
            this.TileWidth.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TileWidth.Name = "TileWidth";
            this.TileWidth.Size = new System.Drawing.Size(92, 26);
            this.TileWidth.TabIndex = 1;
            this.TileWidth.Value = new decimal(new int[] {
            32,
            0,
            0,
            0});
            this.TileWidth.ValueChanged += new System.EventHandler(this.TileWidth_ValueChanged);
            // 
            // TileHeight
            // 
            this.TileHeight.Location = new System.Drawing.Point(92, 78);
            this.TileHeight.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TileHeight.Name = "TileHeight";
            this.TileHeight.Size = new System.Drawing.Size(92, 26);
            this.TileHeight.TabIndex = 2;
            this.TileHeight.Value = new decimal(new int[] {
            32,
            0,
            0,
            0});
            this.TileHeight.ValueChanged += new System.EventHandler(this.TileHeight_ValueChanged);
            // 
            // ObstacleCheckbox
            // 
            this.ObstacleCheckbox.AutoSize = true;
            this.ObstacleCheckbox.Location = new System.Drawing.Point(24, 137);
            this.ObstacleCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ObstacleCheckbox.Name = "ObstacleCheckbox";
            this.ObstacleCheckbox.Size = new System.Drawing.Size(98, 24);
            this.ObstacleCheckbox.TabIndex = 3;
            this.ObstacleCheckbox.Text = "Obstacle";
            this.ObstacleCheckbox.UseVisualStyleBackColor = true;
            this.ObstacleCheckbox.CheckedChanged += new System.EventHandler(this.ObstacleCheckbox_CheckedChanged);
            // 
            // SelectTilesetTexture
            // 
            this.SelectTilesetTexture.Location = new System.Drawing.Point(24, 268);
            this.SelectTilesetTexture.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SelectTilesetTexture.Name = "SelectTilesetTexture";
            this.SelectTilesetTexture.Size = new System.Drawing.Size(40, 35);
            this.SelectTilesetTexture.TabIndex = 4;
            this.SelectTilesetTexture.Text = "..";
            this.SelectTilesetTexture.UseVisualStyleBackColor = true;
            this.SelectTilesetTexture.Click += new System.EventHandler(this.SelectTilesetTexture_Click);
            // 
            // TilesetFilenameText
            // 
            this.TilesetFilenameText.AutoSize = true;
            this.TilesetFilenameText.Location = new System.Drawing.Point(74, 276);
            this.TilesetFilenameText.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.TilesetFilenameText.Name = "TilesetFilenameText";
            this.TilesetFilenameText.Size = new System.Drawing.Size(146, 20);
            this.TilesetFilenameText.TabIndex = 6;
            this.TilesetFilenameText.Text = "No texture selected";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 38);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(50, 20);
            this.label1.TabIndex = 7;
            this.label1.Text = "Width";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(20, 82);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 20);
            this.label2.TabIndex = 8;
            this.label2.Text = "Height";
            // 
            // Tilesets
            // 
            this.Tilesets.FormattingEnabled = true;
            this.Tilesets.Location = new System.Drawing.Point(24, 330);
            this.Tilesets.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Tilesets.Name = "Tilesets";
            this.Tilesets.Size = new System.Drawing.Size(232, 28);
            this.Tilesets.TabIndex = 9;
            this.Tilesets.SelectedIndexChanged += new System.EventHandler(this.Tilesets_SelectedIndexChanged);
            // 
            // AddTilesetButton
            // 
            this.AddTilesetButton.Location = new System.Drawing.Point(24, 373);
            this.AddTilesetButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.AddTilesetButton.Name = "AddTilesetButton";
            this.AddTilesetButton.Size = new System.Drawing.Size(112, 35);
            this.AddTilesetButton.TabIndex = 10;
            this.AddTilesetButton.Text = "&Add";
            this.AddTilesetButton.UseVisualStyleBackColor = true;
            this.AddTilesetButton.Click += new System.EventHandler(this.AddTilesetButton_Click);
            // 
            // RemoveTilesetButton
            // 
            this.RemoveTilesetButton.Location = new System.Drawing.Point(146, 373);
            this.RemoveTilesetButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.RemoveTilesetButton.Name = "RemoveTilesetButton";
            this.RemoveTilesetButton.Size = new System.Drawing.Size(112, 35);
            this.RemoveTilesetButton.TabIndex = 11;
            this.RemoveTilesetButton.Text = "&Remove";
            this.RemoveTilesetButton.UseVisualStyleBackColor = true;
            this.RemoveTilesetButton.Click += new System.EventHandler(this.RemoveTilesetButton_Click);
            // 
            // SaveButton
            // 
            this.SaveButton.Location = new System.Drawing.Point(24, 417);
            this.SaveButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.Size = new System.Drawing.Size(112, 35);
            this.SaveButton.TabIndex = 12;
            this.SaveButton.Text = "&Save all";
            this.SaveButton.UseVisualStyleBackColor = true;
            this.SaveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // DestructableCheckbox
            // 
            this.DestructableCheckbox.AutoSize = true;
            this.DestructableCheckbox.Location = new System.Drawing.Point(24, 172);
            this.DestructableCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.DestructableCheckbox.Name = "DestructableCheckbox";
            this.DestructableCheckbox.Size = new System.Drawing.Size(126, 24);
            this.DestructableCheckbox.TabIndex = 13;
            this.DestructableCheckbox.Text = "Destructable";
            this.DestructableCheckbox.UseVisualStyleBackColor = true;
            this.DestructableCheckbox.CheckedChanged += new System.EventHandler(this.DestructableCheckbox_CheckedChanged);
            // 
            // AutoTileBtn
            // 
            this.AutoTileBtn.Location = new System.Drawing.Point(24, 463);
            this.AutoTileBtn.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.AutoTileBtn.Name = "AutoTileBtn";
            this.AutoTileBtn.Size = new System.Drawing.Size(112, 35);
            this.AutoTileBtn.TabIndex = 14;
            this.AutoTileBtn.Text = "AutoTiles";
            this.AutoTileBtn.UseVisualStyleBackColor = true;
            this.AutoTileBtn.Click += new System.EventHandler(this.AutoTileBtn_Click);
            // 
            // FalloutCheckBox
            // 
            this.FalloutCheckBox.AutoSize = true;
            this.FalloutCheckBox.Location = new System.Drawing.Point(24, 206);
            this.FalloutCheckBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.FalloutCheckBox.Name = "FalloutCheckBox";
            this.FalloutCheckBox.Size = new System.Drawing.Size(83, 24);
            this.FalloutCheckBox.TabIndex = 15;
            this.FalloutCheckBox.Text = "Fallout";
            this.FalloutCheckBox.UseVisualStyleBackColor = true;
            this.FalloutCheckBox.CheckedChanged += new System.EventHandler(this.FalloutCheckBox_CheckedChanged);
            // 
            // TilesetEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1200, 554);
            this.Controls.Add(this.FalloutCheckBox);
            this.Controls.Add(this.AutoTileBtn);
            this.Controls.Add(this.DestructableCheckbox);
            this.Controls.Add(this.SaveButton);
            this.Controls.Add(this.RemoveTilesetButton);
            this.Controls.Add(this.AddTilesetButton);
            this.Controls.Add(this.Tilesets);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.TilesetFilenameText);
            this.Controls.Add(this.SelectTilesetTexture);
            this.Controls.Add(this.ObstacleCheckbox);
            this.Controls.Add(this.TileHeight);
            this.Controls.Add(this.TileWidth);
            this.Controls.Add(this.TilesetImage);
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Name = "TilesetEditor";
            this.Text = "TilesetEditor";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.TilesetEditor_FormClosing);
            this.Load += new System.EventHandler(this.TilesetEditor_Load);
            ((System.ComponentModel.ISupportInitialize)(this.TilesetImage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TileWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TileHeight)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox TilesetImage;
        private System.Windows.Forms.NumericUpDown TileWidth;
        private System.Windows.Forms.NumericUpDown TileHeight;
        private System.Windows.Forms.CheckBox ObstacleCheckbox;
        private System.Windows.Forms.Button SelectTilesetTexture;
        private System.Windows.Forms.Label TilesetFilenameText;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox Tilesets;
        private System.Windows.Forms.Button AddTilesetButton;
        private System.Windows.Forms.Button RemoveTilesetButton;
        private System.Windows.Forms.Button SaveButton;
        private System.Windows.Forms.CheckBox DestructableCheckbox;
        private System.Windows.Forms.Button AutoTileBtn;
        private System.Windows.Forms.CheckBox FalloutCheckBox;
    }
}