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
            this.specialToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.createFrameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
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
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.DefaultValueLabel = new System.Windows.Forms.Label();
            this.VariableDefaultValue = new System.Windows.Forms.NumericUpDown();
            this.VariableListBox = new System.Windows.Forms.ListBox();
            ((System.ComponentModel.ISupportInitialize)(this.Tileset)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TilePreview)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.MapContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Map)).BeginInit();
            this.EditTab.SuspendLayout();
            this.TilesetTab.SuspendLayout();
            this.ObjectsTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ObjectTypePrevPic)).BeginInit();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableDefaultValue)).BeginInit();
            this.SuspendLayout();
            // 
            // Tileset
            // 
            this.Tileset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Tileset.Enabled = false;
            this.Tileset.Location = new System.Drawing.Point(9, 49);
            this.Tileset.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Tileset.Name = "Tileset";
            this.Tileset.Size = new System.Drawing.Size(88, 90);
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
            this.TilePreview.Location = new System.Drawing.Point(9, 149);
            this.TilePreview.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TilePreview.Name = "TilePreview";
            this.TilePreview.Size = new System.Drawing.Size(88, 76);
            this.TilePreview.TabIndex = 2;
            this.TilePreview.TabStop = false;
            this.TilePreview.Paint += new System.Windows.Forms.PaintEventHandler(this.TilePreview_Paint);
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(2, 2, 0, 2);
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editorsToolStripMenuItem,
            this.specialToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1442, 33);
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
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(54, 32);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(176, 34);
            this.newToolStripMenuItem.Text = "&New";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(176, 34);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.OpenToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(176, 34);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.SaveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(176, 34);
            this.saveAsToolStripMenuItem.Text = "Save &As";
            // 
            // quitToolStripMenuItem
            // 
            this.quitToolStripMenuItem.Name = "quitToolStripMenuItem";
            this.quitToolStripMenuItem.Size = new System.Drawing.Size(176, 34);
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
            this.editorsToolStripMenuItem.Size = new System.Drawing.Size(83, 32);
            this.editorsToolStripMenuItem.Text = "Editors";
            // 
            // tilesetEditorToolStripMenuItem
            // 
            this.tilesetEditorToolStripMenuItem.Name = "tilesetEditorToolStripMenuItem";
            this.tilesetEditorToolStripMenuItem.Size = new System.Drawing.Size(311, 34);
            this.tilesetEditorToolStripMenuItem.Text = "Tileset Editor";
            this.tilesetEditorToolStripMenuItem.Click += new System.EventHandler(this.TilesetEditorToolStripMenuItem_Click);
            // 
            // gameObjectTypeEditorToolStripMenuItem
            // 
            this.gameObjectTypeEditorToolStripMenuItem.Name = "gameObjectTypeEditorToolStripMenuItem";
            this.gameObjectTypeEditorToolStripMenuItem.Size = new System.Drawing.Size(311, 34);
            this.gameObjectTypeEditorToolStripMenuItem.Text = "Game Object Type Editor";
            this.gameObjectTypeEditorToolStripMenuItem.Click += new System.EventHandler(this.GameObjectTypeEditorToolStripMenuItem_Click);
            // 
            // mapSettingsToolStripMenuItem
            // 
            this.mapSettingsToolStripMenuItem.Name = "mapSettingsToolStripMenuItem";
            this.mapSettingsToolStripMenuItem.Size = new System.Drawing.Size(311, 34);
            this.mapSettingsToolStripMenuItem.Text = "Map settings";
            this.mapSettingsToolStripMenuItem.Click += new System.EventHandler(this.mapSettingsToolStripMenuItem_Click);
            // 
            // specialToolStripMenuItem
            // 
            this.specialToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.createFrameToolStripMenuItem});
            this.specialToolStripMenuItem.Name = "specialToolStripMenuItem";
            this.specialToolStripMenuItem.Size = new System.Drawing.Size(83, 32);
            this.specialToolStripMenuItem.Text = "&Special";
            // 
            // createFrameToolStripMenuItem
            // 
            this.createFrameToolStripMenuItem.Name = "createFrameToolStripMenuItem";
            this.createFrameToolStripMenuItem.Size = new System.Drawing.Size(215, 34);
            this.createFrameToolStripMenuItem.Text = "&Create frame";
            this.createFrameToolStripMenuItem.Click += new System.EventHandler(this.createFrameToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 12);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 20);
            this.label1.TabIndex = 4;
            this.label1.Text = "Tileset";
            // 
            // Tilesets
            // 
            this.Tilesets.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.Tilesets.FormattingEnabled = true;
            this.Tilesets.Location = new System.Drawing.Point(78, 8);
            this.Tilesets.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Tilesets.Name = "Tilesets";
            this.Tilesets.Size = new System.Drawing.Size(180, 28);
            this.Tilesets.TabIndex = 5;
            this.Tilesets.SelectedIndexChanged += new System.EventHandler(this.Tilesets_SelectedIndexChanged);
            // 
            // MapContainer
            // 
            this.MapContainer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.MapContainer.Controls.Add(this.Map);
            this.MapContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MapContainer.Location = new System.Drawing.Point(0, 33);
            this.MapContainer.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MapContainer.Name = "MapContainer";
            this.MapContainer.Size = new System.Drawing.Size(1442, 756);
            this.MapContainer.TabIndex = 6;
            // 
            // Map
            // 
            this.Map.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Map.Enabled = false;
            this.Map.Location = new System.Drawing.Point(336, 5);
            this.Map.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Map.Name = "Map";
            this.Map.Size = new System.Drawing.Size(1026, 700);
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
            this.vMapScroll.Location = new System.Drawing.Point(1417, 33);
            this.vMapScroll.Name = "vMapScroll";
            this.vMapScroll.Size = new System.Drawing.Size(25, 756);
            this.vMapScroll.TabIndex = 7;
            this.vMapScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.VMapScroll_Scroll);
            // 
            // hMapScroll
            // 
            this.hMapScroll.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hMapScroll.Location = new System.Drawing.Point(0, 787);
            this.hMapScroll.Name = "hMapScroll";
            this.hMapScroll.Size = new System.Drawing.Size(1417, 2);
            this.hMapScroll.TabIndex = 8;
            this.hMapScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.HMapScroll_Scroll);
            // 
            // EditTab
            // 
            this.EditTab.Controls.Add(this.TilesetTab);
            this.EditTab.Controls.Add(this.ObjectsTab);
            this.EditTab.Controls.Add(this.tabPage1);
            this.EditTab.Dock = System.Windows.Forms.DockStyle.Left;
            this.EditTab.Location = new System.Drawing.Point(0, 33);
            this.EditTab.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.EditTab.Name = "EditTab";
            this.EditTab.SelectedIndex = 0;
            this.EditTab.Size = new System.Drawing.Size(300, 754);
            this.EditTab.TabIndex = 9;
            // 
            // TilesetTab
            // 
            this.TilesetTab.Controls.Add(this.Tileset);
            this.TilesetTab.Controls.Add(this.TilePreview);
            this.TilesetTab.Controls.Add(this.Tilesets);
            this.TilesetTab.Controls.Add(this.label1);
            this.TilesetTab.Location = new System.Drawing.Point(4, 29);
            this.TilesetTab.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TilesetTab.Name = "TilesetTab";
            this.TilesetTab.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TilesetTab.Size = new System.Drawing.Size(292, 721);
            this.TilesetTab.TabIndex = 0;
            this.TilesetTab.Text = "Tileset";
            this.TilesetTab.UseVisualStyleBackColor = true;
            // 
            // ObjectsTab
            // 
            this.ObjectsTab.Controls.Add(this.ObjectTypePrevPic);
            this.ObjectsTab.Controls.Add(this.label2);
            this.ObjectsTab.Controls.Add(this.GameObjectTypesList);
            this.ObjectsTab.Location = new System.Drawing.Point(4, 29);
            this.ObjectsTab.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ObjectsTab.Name = "ObjectsTab";
            this.ObjectsTab.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ObjectsTab.Size = new System.Drawing.Size(95, 721);
            this.ObjectsTab.TabIndex = 1;
            this.ObjectsTab.Text = "Objects";
            this.ObjectsTab.UseVisualStyleBackColor = true;
            // 
            // ObjectTypePrevPic
            // 
            this.ObjectTypePrevPic.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ObjectTypePrevPic.Location = new System.Drawing.Point(9, 192);
            this.ObjectTypePrevPic.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ObjectTypePrevPic.Name = "ObjectTypePrevPic";
            this.ObjectTypePrevPic.Size = new System.Drawing.Size(184, 92);
            this.ObjectTypePrevPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.ObjectTypePrevPic.TabIndex = 2;
            this.ObjectTypePrevPic.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 11);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 20);
            this.label2.TabIndex = 1;
            this.label2.Text = "Types";
            // 
            // GameObjectTypesList
            // 
            this.GameObjectTypesList.FormattingEnabled = true;
            this.GameObjectTypesList.ItemHeight = 20;
            this.GameObjectTypesList.Location = new System.Drawing.Point(9, 37);
            this.GameObjectTypesList.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GameObjectTypesList.Name = "GameObjectTypesList";
            this.GameObjectTypesList.Size = new System.Drawing.Size(274, 144);
            this.GameObjectTypesList.TabIndex = 0;
            this.GameObjectTypesList.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GameObjectTypesList_MouseDown);
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.DefaultValueLabel);
            this.tabPage1.Controls.Add(this.VariableDefaultValue);
            this.tabPage1.Controls.Add(this.VariableListBox);
            this.tabPage1.Location = new System.Drawing.Point(4, 29);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Size = new System.Drawing.Size(95, 721);
            this.tabPage1.TabIndex = 2;
            this.tabPage1.Text = "Object Data";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // DefaultValueLabel
            // 
            this.DefaultValueLabel.AutoSize = true;
            this.DefaultValueLabel.Location = new System.Drawing.Point(16, 182);
            this.DefaultValueLabel.Name = "DefaultValueLabel";
            this.DefaultValueLabel.Size = new System.Drawing.Size(102, 20);
            this.DefaultValueLabel.TabIndex = 8;
            this.DefaultValueLabel.Text = "Default value";
            // 
            // VariableDefaultValue
            // 
            this.VariableDefaultValue.DecimalPlaces = 2;
            this.VariableDefaultValue.Location = new System.Drawing.Point(20, 214);
            this.VariableDefaultValue.Name = "VariableDefaultValue";
            this.VariableDefaultValue.Size = new System.Drawing.Size(120, 26);
            this.VariableDefaultValue.TabIndex = 7;
            // 
            // VariableListBox
            // 
            this.VariableListBox.FormattingEnabled = true;
            this.VariableListBox.ItemHeight = 20;
            this.VariableListBox.Location = new System.Drawing.Point(20, 24);
            this.VariableListBox.Name = "VariableListBox";
            this.VariableListBox.Size = new System.Drawing.Size(227, 144);
            this.VariableListBox.TabIndex = 6;
            // 
            // MapEditor
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1442, 789);
            this.Controls.Add(this.EditTab);
            this.Controls.Add(this.hMapScroll);
            this.Controls.Add(this.vMapScroll);
            this.Controls.Add(this.MapContainer);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
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
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableDefaultValue)).EndInit();
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
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.Label DefaultValueLabel;
        private System.Windows.Forms.NumericUpDown VariableDefaultValue;
        private System.Windows.Forms.ListBox VariableListBox;
    }
}

