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
            this.animationEditorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.enemyTypeEditorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
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
            this.ObjectData = new System.Windows.Forms.TabPage();
            this.DefaultValueLabel = new System.Windows.Forms.Label();
            this.VariableDefaultValue = new System.Windows.Forms.NumericUpDown();
            this.VariableListBox = new System.Windows.Forms.ListBox();
            this.Enemies = new System.Windows.Forms.TabPage();
            this.EnemyPreviewPic = new System.Windows.Forms.PictureBox();
            this.EnemiesLabel = new System.Windows.Forms.Label();
            this.EnemyList = new System.Windows.Forms.ListBox();
            ((System.ComponentModel.ISupportInitialize)(this.Tileset)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TilePreview)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.MapContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Map)).BeginInit();
            this.EditTab.SuspendLayout();
            this.TilesetTab.SuspendLayout();
            this.ObjectsTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ObjectTypePrevPic)).BeginInit();
            this.ObjectData.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableDefaultValue)).BeginInit();
            this.Enemies.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.EnemyPreviewPic)).BeginInit();
            this.SuspendLayout();
            // 
            // Tileset
            // 
            this.Tileset.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Tileset.Enabled = false;
            this.Tileset.Location = new System.Drawing.Point(16, 76);
            this.Tileset.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.Tileset.Name = "Tileset";
            this.Tileset.Size = new System.Drawing.Size(155, 138);
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
            this.TilePreview.Location = new System.Drawing.Point(16, 231);
            this.TilePreview.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.TilePreview.Name = "TilePreview";
            this.TilePreview.Size = new System.Drawing.Size(155, 117);
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
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(11, 3, 0, 3);
            this.menuStrip1.Size = new System.Drawing.Size(2564, 60);
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
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(87, 54);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(285, 54);
            this.newToolStripMenuItem.Text = "&New";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(285, 54);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.OpenToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(285, 54);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.SaveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(285, 54);
            this.saveAsToolStripMenuItem.Text = "Save &As";
            // 
            // quitToolStripMenuItem
            // 
            this.quitToolStripMenuItem.Name = "quitToolStripMenuItem";
            this.quitToolStripMenuItem.Size = new System.Drawing.Size(285, 54);
            this.quitToolStripMenuItem.Text = "&Quit";
            this.quitToolStripMenuItem.Click += new System.EventHandler(this.QuitToolStripMenuItem_Click);
            // 
            // editorsToolStripMenuItem
            // 
            this.editorsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tilesetEditorToolStripMenuItem,
            this.gameObjectTypeEditorToolStripMenuItem,
            this.mapSettingsToolStripMenuItem,
            this.animationEditorToolStripMenuItem,
            this.enemyTypeEditorToolStripMenuItem});
            this.editorsToolStripMenuItem.Name = "editorsToolStripMenuItem";
            this.editorsToolStripMenuItem.Size = new System.Drawing.Size(133, 54);
            this.editorsToolStripMenuItem.Text = "Editors";
            // 
            // tilesetEditorToolStripMenuItem
            // 
            this.tilesetEditorToolStripMenuItem.Name = "tilesetEditorToolStripMenuItem";
            this.tilesetEditorToolStripMenuItem.Size = new System.Drawing.Size(515, 54);
            this.tilesetEditorToolStripMenuItem.Text = "Tileset Editor";
            this.tilesetEditorToolStripMenuItem.Click += new System.EventHandler(this.TilesetEditorToolStripMenuItem_Click);
            // 
            // gameObjectTypeEditorToolStripMenuItem
            // 
            this.gameObjectTypeEditorToolStripMenuItem.Name = "gameObjectTypeEditorToolStripMenuItem";
            this.gameObjectTypeEditorToolStripMenuItem.Size = new System.Drawing.Size(515, 54);
            this.gameObjectTypeEditorToolStripMenuItem.Text = "Game Object Type Editor";
            this.gameObjectTypeEditorToolStripMenuItem.Click += new System.EventHandler(this.GameObjectTypeEditorToolStripMenuItem_Click);
            // 
            // mapSettingsToolStripMenuItem
            // 
            this.mapSettingsToolStripMenuItem.Name = "mapSettingsToolStripMenuItem";
            this.mapSettingsToolStripMenuItem.Size = new System.Drawing.Size(515, 54);
            this.mapSettingsToolStripMenuItem.Text = "Map settings";
            this.mapSettingsToolStripMenuItem.Click += new System.EventHandler(this.mapSettingsToolStripMenuItem_Click);
            // 
            // animationEditorToolStripMenuItem
            // 
            this.animationEditorToolStripMenuItem.Name = "animationEditorToolStripMenuItem";
            this.animationEditorToolStripMenuItem.Size = new System.Drawing.Size(515, 54);
            this.animationEditorToolStripMenuItem.Text = "Animation Editor";
            // 
            // enemyTypeEditorToolStripMenuItem
            // 
            this.enemyTypeEditorToolStripMenuItem.Name = "enemyTypeEditorToolStripMenuItem";
            this.enemyTypeEditorToolStripMenuItem.Size = new System.Drawing.Size(515, 54);
            this.enemyTypeEditorToolStripMenuItem.Text = "Enemy Type Editor";
            this.enemyTypeEditorToolStripMenuItem.Click += new System.EventHandler(this.enemyTypeEditorToolStripMenuItem_Click);
            // 
            // specialToolStripMenuItem
            // 
            this.specialToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.createFrameToolStripMenuItem});
            this.specialToolStripMenuItem.Name = "specialToolStripMenuItem";
            this.specialToolStripMenuItem.Size = new System.Drawing.Size(135, 54);
            this.specialToolStripMenuItem.Text = "&Special";
            // 
            // createFrameToolStripMenuItem
            // 
            this.createFrameToolStripMenuItem.Name = "createFrameToolStripMenuItem";
            this.createFrameToolStripMenuItem.Size = new System.Drawing.Size(354, 54);
            this.createFrameToolStripMenuItem.Text = "&Create frame";
            this.createFrameToolStripMenuItem.Click += new System.EventHandler(this.createFrameToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 19);
            this.label1.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 20);
            this.label1.TabIndex = 4;
            this.label1.Text = "Tileset";
            // 
            // Tilesets
            // 
            this.Tilesets.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.Tilesets.FormattingEnabled = true;
            this.Tilesets.Location = new System.Drawing.Point(139, 12);
            this.Tilesets.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.Tilesets.Name = "Tilesets";
            this.Tilesets.Size = new System.Drawing.Size(317, 39);
            this.Tilesets.TabIndex = 5;
            this.Tilesets.SelectedIndexChanged += new System.EventHandler(this.Tilesets_SelectedIndexChanged);
            // 
            // MapContainer
            // 
            this.MapContainer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.MapContainer.Controls.Add(this.Map);
            this.MapContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MapContainer.Location = new System.Drawing.Point(0, 60);
            this.MapContainer.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.MapContainer.Name = "MapContainer";
            this.MapContainer.Size = new System.Drawing.Size(2564, 1163);
            this.MapContainer.TabIndex = 6;
            this.MapContainer.Paint += new System.Windows.Forms.PaintEventHandler(this.MapContainer_Paint);
            // 
            // Map
            // 
            this.Map.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Map.Enabled = false;
            this.Map.Location = new System.Drawing.Point(686, 6);
            this.Map.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.Map.Name = "Map";
            this.Map.Size = new System.Drawing.Size(1822, 1084);
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
            this.vMapScroll.Location = new System.Drawing.Point(2539, 60);
            this.vMapScroll.Name = "vMapScroll";
            this.vMapScroll.Size = new System.Drawing.Size(25, 1163);
            this.vMapScroll.TabIndex = 7;
            this.vMapScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.VMapScroll_Scroll);
            // 
            // hMapScroll
            // 
            this.hMapScroll.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hMapScroll.Location = new System.Drawing.Point(0, 1221);
            this.hMapScroll.Name = "hMapScroll";
            this.hMapScroll.Size = new System.Drawing.Size(2539, 2);
            this.hMapScroll.TabIndex = 8;
            this.hMapScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.HMapScroll_Scroll);
            // 
            // EditTab
            // 
            this.EditTab.Controls.Add(this.TilesetTab);
            this.EditTab.Controls.Add(this.ObjectsTab);
            this.EditTab.Controls.Add(this.ObjectData);
            this.EditTab.Controls.Add(this.Enemies);
            this.EditTab.Dock = System.Windows.Forms.DockStyle.Left;
            this.EditTab.Location = new System.Drawing.Point(0, 60);
            this.EditTab.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.EditTab.Name = "EditTab";
            this.EditTab.SelectedIndex = 0;
            this.EditTab.Size = new System.Drawing.Size(551, 1161);
            this.EditTab.TabIndex = 9;
            // 
            // TilesetTab
            // 
            this.TilesetTab.Controls.Add(this.Tileset);
            this.TilesetTab.Controls.Add(this.TilePreview);
            this.TilesetTab.Controls.Add(this.Tilesets);
            this.TilesetTab.Controls.Add(this.label1);
            this.TilesetTab.Location = new System.Drawing.Point(10, 48);
            this.TilesetTab.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.TilesetTab.Name = "TilesetTab";
            this.TilesetTab.Padding = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.TilesetTab.Size = new System.Drawing.Size(531, 1103);
            this.TilesetTab.TabIndex = 0;
            this.TilesetTab.Text = "Tileset";
            this.TilesetTab.UseVisualStyleBackColor = true;
            // 
            // ObjectsTab
            // 
            this.ObjectsTab.Controls.Add(this.ObjectTypePrevPic);
            this.ObjectsTab.Controls.Add(this.label2);
            this.ObjectsTab.Controls.Add(this.GameObjectTypesList);
            this.ObjectsTab.Location = new System.Drawing.Point(10, 48);
            this.ObjectsTab.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.ObjectsTab.Name = "ObjectsTab";
            this.ObjectsTab.Padding = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.ObjectsTab.Size = new System.Drawing.Size(531, 1111);
            this.ObjectsTab.TabIndex = 1;
            this.ObjectsTab.Text = "Objects";
            this.ObjectsTab.UseVisualStyleBackColor = true;
            // 
            // ObjectTypePrevPic
            // 
            this.ObjectTypePrevPic.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ObjectTypePrevPic.Location = new System.Drawing.Point(16, 298);
            this.ObjectTypePrevPic.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.ObjectTypePrevPic.Name = "ObjectTypePrevPic";
            this.ObjectTypePrevPic.Size = new System.Drawing.Size(184, 92);
            this.ObjectTypePrevPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.ObjectTypePrevPic.TabIndex = 2;
            this.ObjectTypePrevPic.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 17);
            this.label2.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 20);
            this.label2.TabIndex = 1;
            this.label2.Text = "Types";
            // 
            // GameObjectTypesList
            // 
            this.GameObjectTypesList.FormattingEnabled = true;
            this.GameObjectTypesList.ItemHeight = 31;
            this.GameObjectTypesList.Location = new System.Drawing.Point(16, 57);
            this.GameObjectTypesList.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.GameObjectTypesList.Name = "GameObjectTypesList";
            this.GameObjectTypesList.Size = new System.Drawing.Size(484, 221);
            this.GameObjectTypesList.TabIndex = 0;
            this.GameObjectTypesList.SelectedIndexChanged += new System.EventHandler(this.GameObjectTypesList_SelectedIndexChanged_1);
            this.GameObjectTypesList.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GameObjectTypesList_MouseDown);
            // 
            // ObjectData
            // 
            this.ObjectData.Controls.Add(this.DefaultValueLabel);
            this.ObjectData.Controls.Add(this.VariableDefaultValue);
            this.ObjectData.Controls.Add(this.VariableListBox);
            this.ObjectData.Location = new System.Drawing.Point(10, 48);
            this.ObjectData.Margin = new System.Windows.Forms.Padding(5, 5, 5, 5);
            this.ObjectData.Name = "ObjectData";
            this.ObjectData.Size = new System.Drawing.Size(531, 1111);
            this.ObjectData.TabIndex = 2;
            this.ObjectData.Text = "Object Data";
            this.ObjectData.UseVisualStyleBackColor = true;
            // 
            // DefaultValueLabel
            // 
            this.DefaultValueLabel.AutoSize = true;
            this.DefaultValueLabel.Location = new System.Drawing.Point(28, 282);
            this.DefaultValueLabel.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.DefaultValueLabel.Name = "DefaultValueLabel";
            this.DefaultValueLabel.Size = new System.Drawing.Size(102, 20);
            this.DefaultValueLabel.TabIndex = 8;
            this.DefaultValueLabel.Text = "Default value";
            // 
            // VariableDefaultValue
            // 
            this.VariableDefaultValue.DecimalPlaces = 2;
            this.VariableDefaultValue.Location = new System.Drawing.Point(36, 332);
            this.VariableDefaultValue.Margin = new System.Windows.Forms.Padding(5, 5, 5, 5);
            this.VariableDefaultValue.Name = "VariableDefaultValue";
            this.VariableDefaultValue.Size = new System.Drawing.Size(213, 26);
            this.VariableDefaultValue.TabIndex = 7;
            // 
            // VariableListBox
            // 
            this.VariableListBox.FormattingEnabled = true;
            this.VariableListBox.ItemHeight = 31;
            this.VariableListBox.Location = new System.Drawing.Point(36, 37);
            this.VariableListBox.Margin = new System.Windows.Forms.Padding(5, 5, 5, 5);
            this.VariableListBox.Name = "VariableListBox";
            this.VariableListBox.Size = new System.Drawing.Size(400, 221);
            this.VariableListBox.TabIndex = 6;
            // 
            // Enemies
            // 
            this.Enemies.Controls.Add(this.EnemyPreviewPic);
            this.Enemies.Controls.Add(this.EnemiesLabel);
            this.Enemies.Controls.Add(this.EnemyList);
            this.Enemies.Location = new System.Drawing.Point(10, 48);
            this.Enemies.Margin = new System.Windows.Forms.Padding(5, 5, 5, 5);
            this.Enemies.Name = "Enemies";
            this.Enemies.Size = new System.Drawing.Size(531, 1111);
            this.Enemies.TabIndex = 3;
            this.Enemies.Text = "Enemies";
            this.Enemies.UseVisualStyleBackColor = true;
            // 
            // EnemyPreviewPic
            // 
            this.EnemyPreviewPic.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.EnemyPreviewPic.Location = new System.Drawing.Point(16, 296);
            this.EnemyPreviewPic.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.EnemyPreviewPic.Name = "EnemyPreviewPic";
            this.EnemyPreviewPic.Size = new System.Drawing.Size(184, 92);
            this.EnemyPreviewPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.EnemyPreviewPic.TabIndex = 5;
            this.EnemyPreviewPic.TabStop = false;
            // 
            // EnemiesLabel
            // 
            this.EnemiesLabel.AutoSize = true;
            this.EnemiesLabel.Location = new System.Drawing.Point(18, 16);
            this.EnemiesLabel.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.EnemiesLabel.Name = "EnemiesLabel";
            this.EnemiesLabel.Size = new System.Drawing.Size(71, 20);
            this.EnemiesLabel.TabIndex = 4;
            this.EnemiesLabel.Text = "Enemies";
            // 
            // EnemyList
            // 
            this.EnemyList.FormattingEnabled = true;
            this.EnemyList.ItemHeight = 31;
            this.EnemyList.Location = new System.Drawing.Point(16, 56);
            this.EnemyList.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.EnemyList.Name = "EnemyList";
            this.EnemyList.Size = new System.Drawing.Size(484, 221);
            this.EnemyList.TabIndex = 3;
            this.EnemyList.SelectedIndexChanged += new System.EventHandler(this.EnemyList_SelectedIndexChanged);
            this.EnemyList.MouseDown += new System.Windows.Forms.MouseEventHandler(this.EnemyList_MouseDown);
            // 
            // MapEditor
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(2564, 1223);
            this.Controls.Add(this.EditTab);
            this.Controls.Add(this.hMapScroll);
            this.Controls.Add(this.vMapScroll);
            this.Controls.Add(this.MapContainer);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
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
            this.ObjectData.ResumeLayout(false);
            this.ObjectData.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableDefaultValue)).EndInit();
            this.Enemies.ResumeLayout(false);
            this.Enemies.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.EnemyPreviewPic)).EndInit();
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
        private System.Windows.Forms.TabPage ObjectData;
        private System.Windows.Forms.Label DefaultValueLabel;
        private System.Windows.Forms.NumericUpDown VariableDefaultValue;
        private System.Windows.Forms.ListBox VariableListBox;
        private System.Windows.Forms.ToolStripMenuItem animationEditorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem enemyTypeEditorToolStripMenuItem;
        private System.Windows.Forms.TabPage Enemies;
        private System.Windows.Forms.PictureBox EnemyPreviewPic;
        private System.Windows.Forms.Label EnemiesLabel;
        private System.Windows.Forms.ListBox EnemyList;
    }
}

