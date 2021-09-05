namespace PlatformEditor
{
    partial class MapEditor
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
            this.Tileset = new System.Windows.Forms.PictureBox();
            this.TilePreview = new System.Windows.Forms.PictureBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.quitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editorsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tilesetEditorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.gameObjectTypeEditorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mapSettingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.Tilesets = new System.Windows.Forms.ComboBox();
            this.MapContainer = new System.Windows.Forms.Panel();
            this.Map = new System.Windows.Forms.PictureBox();
            this.vMapScroll = new System.Windows.Forms.VScrollBar();
            this.hMapScroll = new System.Windows.Forms.HScrollBar();
            this.EditTab = new System.Windows.Forms.TabControl();
            this.TilesetTab = new System.Windows.Forms.TabPage();
            this.ObjectsTab = new System.Windows.Forms.TabPage();
            this.ObjectTypePrevPic = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.GameObjectTypesList = new System.Windows.Forms.ListBox();
            this.specialToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.createFrameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.Tileset)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TilePreview)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.MapContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Map)).BeginInit();
            this.EditTab.SuspendLayout();
            this.TilesetTab.SuspendLayout();
            this.ObjectsTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ObjectTypePrevPic)).BeginInit();
            this.SuspendLayout();
            // 
            // Tileset
            // 
            this.Tileset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Tileset.Enabled = false;
            this.Tileset.Location = new System.Drawing.Point(6, 32);
            this.Tileset.Name = "Tileset";
            this.Tileset.Size = new System.Drawing.Size(59, 59);
            this.Tileset.TabIndex = 1;
            this.Tileset.TabStop = false;
            this.Tileset.Click += new System.EventHandler(this.Tileset_Click);
            this.Tileset.Paint += new System.Windows.Forms.PaintEventHandler(this.Tileset_Paint);
            this.Tileset.MouseEnter += new System.EventHandler(this.Tileset_MouseEnter);
            this.Tileset.MouseLeave += new System.EventHandler(this.Tileset_MouseLeave);
            this.Tileset.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Tileset_MouseMove);
            // 
            // TilePreview
            // 
            this.TilePreview.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TilePreview.Location = new System.Drawing.Point(6, 97);
            this.TilePreview.Name = "TilePreview";
            this.TilePreview.Size = new System.Drawing.Size(59, 50);
            this.TilePreview.TabIndex = 2;
            this.TilePreview.TabStop = false;
            this.TilePreview.Paint += new System.Windows.Forms.PaintEventHandler(this.TilePreview_Paint);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editorsToolStripMenuItem,
            this.specialToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(937, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.MenuStrip1_ItemClicked);
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.quitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.newToolStripMenuItem.Text = "&New";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.OpenToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.SaveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.saveAsToolStripMenuItem.Text = "Save &As";
            // 
            // quitToolStripMenuItem
            // 
            this.quitToolStripMenuItem.Name = "quitToolStripMenuItem";
            this.quitToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.quitToolStripMenuItem.Text = "&Quit";
            this.quitToolStripMenuItem.Click += new System.EventHandler(this.QuitToolStripMenuItem_Click);
            // 
            // editorsToolStripMenuItem
            // 
            this.editorsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tilesetEditorToolStripMenuItem,
            this.gameObjectTypeEditorToolStripMenuItem,
            this.mapSettingsToolStripMenuItem});
            this.editorsToolStripMenuItem.Name = "editorsToolStripMenuItem";
            this.editorsToolStripMenuItem.Size = new System.Drawing.Size(55, 20);
            this.editorsToolStripMenuItem.Text = "Editors";
            // 
            // tilesetEditorToolStripMenuItem
            // 
            this.tilesetEditorToolStripMenuItem.Name = "tilesetEditorToolStripMenuItem";
            this.tilesetEditorToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.tilesetEditorToolStripMenuItem.Text = "Tileset Editor";
            this.tilesetEditorToolStripMenuItem.Click += new System.EventHandler(this.TilesetEditorToolStripMenuItem_Click);
            // 
            // gameObjectTypeEditorToolStripMenuItem
            // 
            this.gameObjectTypeEditorToolStripMenuItem.Name = "gameObjectTypeEditorToolStripMenuItem";
            this.gameObjectTypeEditorToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.gameObjectTypeEditorToolStripMenuItem.Text = "Game Object Type Editor";
            this.gameObjectTypeEditorToolStripMenuItem.Click += new System.EventHandler(this.GameObjectTypeEditorToolStripMenuItem_Click);
            // 
            // mapSettingsToolStripMenuItem
            // 
            this.mapSettingsToolStripMenuItem.Name = "mapSettingsToolStripMenuItem";
            this.mapSettingsToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.mapSettingsToolStripMenuItem.Text = "Map settings";
            this.mapSettingsToolStripMenuItem.Click += new System.EventHandler(this.mapSettingsToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Tileset";
            // 
            // Tilesets
            // 
            this.Tilesets.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.Tilesets.FormattingEnabled = true;
            this.Tilesets.Location = new System.Drawing.Point(52, 5);
            this.Tilesets.Name = "Tilesets";
            this.Tilesets.Size = new System.Drawing.Size(121, 21);
            this.Tilesets.TabIndex = 5;
            this.Tilesets.SelectedIndexChanged += new System.EventHandler(this.Tilesets_SelectedIndexChanged);
            // 
            // MapContainer
            // 
            this.MapContainer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.MapContainer.Controls.Add(this.Map);
            this.MapContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MapContainer.Location = new System.Drawing.Point(0, 24);
            this.MapContainer.Name = "MapContainer";
            this.MapContainer.Size = new System.Drawing.Size(937, 486);
            this.MapContainer.TabIndex = 6;
            // 
            // Map
            // 
            this.Map.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Map.Enabled = false;
            this.Map.Location = new System.Drawing.Point(-1, -1);
            this.Map.Name = "Map";
            this.Map.Size = new System.Drawing.Size(685, 456);
            this.Map.TabIndex = 0;
            this.Map.TabStop = false;
            this.Map.Click += new System.EventHandler(this.Map_Click);
            this.Map.Paint += new System.Windows.Forms.PaintEventHandler(this.Map_Paint);
            this.Map.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Map_MouseDown);
            this.Map.MouseLeave += new System.EventHandler(this.Map_MouseLeave);
            this.Map.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Map_MouseMove);
            this.Map.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Map_MouseUp);
            // 
            // vMapScroll
            // 
            this.vMapScroll.Dock = System.Windows.Forms.DockStyle.Right;
            this.vMapScroll.Location = new System.Drawing.Point(919, 24);
            this.vMapScroll.Name = "vMapScroll";
            this.vMapScroll.Size = new System.Drawing.Size(18, 486);
            this.vMapScroll.TabIndex = 7;
            this.vMapScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.VMapScroll_Scroll);
            // 
            // hMapScroll
            // 
            this.hMapScroll.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hMapScroll.Location = new System.Drawing.Point(0, 495);
            this.hMapScroll.Name = "hMapScroll";
            this.hMapScroll.Size = new System.Drawing.Size(919, 15);
            this.hMapScroll.TabIndex = 8;
            this.hMapScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.HMapScroll_Scroll);
            // 
            // EditTab
            // 
            this.EditTab.Controls.Add(this.TilesetTab);
            this.EditTab.Controls.Add(this.ObjectsTab);
            this.EditTab.Dock = System.Windows.Forms.DockStyle.Left;
            this.EditTab.Location = new System.Drawing.Point(0, 24);
            this.EditTab.Name = "EditTab";
            this.EditTab.SelectedIndex = 0;
            this.EditTab.Size = new System.Drawing.Size(204, 471);
            this.EditTab.TabIndex = 9;
            // 
            // TilesetTab
            // 
            this.TilesetTab.Controls.Add(this.Tileset);
            this.TilesetTab.Controls.Add(this.TilePreview);
            this.TilesetTab.Controls.Add(this.Tilesets);
            this.TilesetTab.Controls.Add(this.label1);
            this.TilesetTab.Location = new System.Drawing.Point(4, 22);
            this.TilesetTab.Name = "TilesetTab";
            this.TilesetTab.Padding = new System.Windows.Forms.Padding(3);
            this.TilesetTab.Size = new System.Drawing.Size(196, 445);
            this.TilesetTab.TabIndex = 0;
            this.TilesetTab.Text = "Tileset";
            this.TilesetTab.UseVisualStyleBackColor = true;
            // 
            // ObjectsTab
            // 
            this.ObjectsTab.Controls.Add(this.ObjectTypePrevPic);
            this.ObjectsTab.Controls.Add(this.label2);
            this.ObjectsTab.Controls.Add(this.GameObjectTypesList);
            this.ObjectsTab.Location = new System.Drawing.Point(4, 22);
            this.ObjectsTab.Name = "ObjectsTab";
            this.ObjectsTab.Padding = new System.Windows.Forms.Padding(3);
            this.ObjectsTab.Size = new System.Drawing.Size(196, 445);
            this.ObjectsTab.TabIndex = 1;
            this.ObjectsTab.Text = "Objects";
            this.ObjectsTab.UseVisualStyleBackColor = true;
            // 
            // ObjectTypePrevPic
            // 
            this.ObjectTypePrevPic.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ObjectTypePrevPic.Location = new System.Drawing.Point(6, 125);
            this.ObjectTypePrevPic.Name = "ObjectTypePrevPic";
            this.ObjectTypePrevPic.Size = new System.Drawing.Size(184, 92);
            this.ObjectTypePrevPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.ObjectTypePrevPic.TabIndex = 2;
            this.ObjectTypePrevPic.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 7);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Types";
            // 
            // GameObjectTypesList
            // 
            this.GameObjectTypesList.FormattingEnabled = true;
            this.GameObjectTypesList.Location = new System.Drawing.Point(6, 24);
            this.GameObjectTypesList.Name = "GameObjectTypesList";
            this.GameObjectTypesList.Size = new System.Drawing.Size(184, 95);
            this.GameObjectTypesList.TabIndex = 0;
            this.GameObjectTypesList.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GameObjectTypesList_MouseDown);
            // 
            // specialToolStripMenuItem
            // 
            this.specialToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.createFrameToolStripMenuItem});
            this.specialToolStripMenuItem.Name = "specialToolStripMenuItem";
            this.specialToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.specialToolStripMenuItem.Text = "&Special";
            // 
            // createFrameToolStripMenuItem
            // 
            this.createFrameToolStripMenuItem.Name = "createFrameToolStripMenuItem";
            this.createFrameToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.createFrameToolStripMenuItem.Text = "&Create frame";
            this.createFrameToolStripMenuItem.Click += new System.EventHandler(this.createFrameToolStripMenuItem_Click);
            // 
            // MapEditor
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(937, 510);
            this.Controls.Add(this.EditTab);
            this.Controls.Add(this.hMapScroll);
            this.Controls.Add(this.vMapScroll);
            this.Controls.Add(this.MapContainer);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MapEditor";
            this.Text = "Platform Editor";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.Tileset)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TilePreview)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.MapContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.Map)).EndInit();
            this.EditTab.ResumeLayout(false);
            this.TilesetTab.ResumeLayout(false);
            this.TilesetTab.PerformLayout();
            this.ObjectsTab.ResumeLayout(false);
            this.ObjectsTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ObjectTypePrevPic)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.PictureBox Tileset;
        private System.Windows.Forms.PictureBox TilePreview;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem quitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editorsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tilesetEditorToolStripMenuItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel MapContainer;
        private System.Windows.Forms.PictureBox Map;
        private System.Windows.Forms.ComboBox Tilesets;
        private System.Windows.Forms.VScrollBar vMapScroll;
        private System.Windows.Forms.HScrollBar hMapScroll;
        private System.Windows.Forms.ToolStripMenuItem gameObjectTypeEditorToolStripMenuItem;
        private System.Windows.Forms.TabControl EditTab;
        private System.Windows.Forms.TabPage TilesetTab;
        private System.Windows.Forms.TabPage ObjectsTab;
        private System.Windows.Forms.PictureBox ObjectTypePrevPic;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListBox GameObjectTypesList;
        private System.Windows.Forms.ToolStripMenuItem mapSettingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem specialToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem createFrameToolStripMenuItem;
    }
}

