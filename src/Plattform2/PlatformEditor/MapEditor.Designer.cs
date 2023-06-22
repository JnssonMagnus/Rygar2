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
            this.MapContainer = new System.Windows.Forms.Panel();
            this.Map = new System.Windows.Forms.PictureBox();
            this.Enemies = new System.Windows.Forms.TabPage();
            this.EnemyPreviewPic = new System.Windows.Forms.PictureBox();
            this.EnemiesLabel = new System.Windows.Forms.Label();
            this.EnemyList = new System.Windows.Forms.ListBox();
            this.ObjectsTab = new System.Windows.Forms.TabPage();
            this.VariableGrid = new System.Windows.Forms.DataGridView();
            this.VariableName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Value = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label3 = new System.Windows.Forms.Label();
            this.ObjectTypePrevPic = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.GameObjectTypesList = new System.Windows.Forms.ListBox();
            this.TilesetTab = new System.Windows.Forms.TabPage();
            this.Tileset = new System.Windows.Forms.PictureBox();
            this.TilePreview = new System.Windows.Forms.PictureBox();
            this.Tilesets = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.EditTab = new System.Windows.Forms.TabControl();
            this.vMapScroll = new System.Windows.Forms.VScrollBar();
            this.hMapScroll = new System.Windows.Forms.HScrollBar();
            this.menuStrip1.SuspendLayout();
            this.MapContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Map)).BeginInit();
            this.Enemies.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.EnemyPreviewPic)).BeginInit();
            this.ObjectsTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ObjectTypePrevPic)).BeginInit();
            this.TilesetTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Tileset)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TilePreview)).BeginInit();
            this.EditTab.SuspendLayout();
            this.SuspendLayout();
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
            this.menuStrip1.Size = new System.Drawing.Size(3367, 54);
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
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(87, 48);
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
            this.editorsToolStripMenuItem.Size = new System.Drawing.Size(133, 48);
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
            this.specialToolStripMenuItem.Size = new System.Drawing.Size(135, 48);
            this.specialToolStripMenuItem.Text = "&Special";
            // 
            // createFrameToolStripMenuItem
            // 
            this.createFrameToolStripMenuItem.Name = "createFrameToolStripMenuItem";
            this.createFrameToolStripMenuItem.Size = new System.Drawing.Size(354, 54);
            this.createFrameToolStripMenuItem.Text = "&Create frame";
            this.createFrameToolStripMenuItem.Click += new System.EventHandler(this.createFrameToolStripMenuItem_Click);
            // 
            // MapContainer
            // 
            this.MapContainer.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.MapContainer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.MapContainer.Controls.Add(this.Map);
            this.MapContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MapContainer.Location = new System.Drawing.Point(0, 54);
            this.MapContainer.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.MapContainer.Name = "MapContainer";
            this.MapContainer.Size = new System.Drawing.Size(3367, 1908);
            this.MapContainer.TabIndex = 6;
            this.MapContainer.Paint += new System.Windows.Forms.PaintEventHandler(this.MapContainer_Paint);
            // 
            // Map
            // 
            this.Map.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Map.Enabled = false;
            this.Map.Location = new System.Drawing.Point(7, -2);
            this.Map.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.Map.Name = "Map";
            this.Map.Size = new System.Drawing.Size(3314, 2070);
            this.Map.TabIndex = 0;
            this.Map.TabStop = false;
            this.Map.Click += new System.EventHandler(this.Map_Click);
            this.Map.Paint += new System.Windows.Forms.PaintEventHandler(this.Map_Paint);
            this.Map.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Map_MouseDown);
            this.Map.MouseLeave += new System.EventHandler(this.Map_MouseLeave);
            this.Map.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Map_MouseMove);
            this.Map.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Map_MouseUp);
            // 
            // Enemies
            // 
            this.Enemies.Controls.Add(this.EnemyPreviewPic);
            this.Enemies.Controls.Add(this.EnemiesLabel);
            this.Enemies.Controls.Add(this.EnemyList);
            this.Enemies.Location = new System.Drawing.Point(10, 48);
            this.Enemies.Margin = new System.Windows.Forms.Padding(5, 5, 5, 5);
            this.Enemies.Name = "Enemies";
            this.Enemies.Size = new System.Drawing.Size(513, 1833);
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
            this.EnemiesLabel.Size = new System.Drawing.Size(125, 32);
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
            // ObjectsTab
            // 
            this.ObjectsTab.Controls.Add(this.VariableGrid);
            this.ObjectsTab.Controls.Add(this.label3);
            this.ObjectsTab.Controls.Add(this.ObjectTypePrevPic);
            this.ObjectsTab.Controls.Add(this.label2);
            this.ObjectsTab.Controls.Add(this.GameObjectTypesList);
            this.ObjectsTab.Location = new System.Drawing.Point(10, 48);
            this.ObjectsTab.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.ObjectsTab.Name = "ObjectsTab";
            this.ObjectsTab.Padding = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.ObjectsTab.Size = new System.Drawing.Size(513, 1830);
            this.ObjectsTab.TabIndex = 1;
            this.ObjectsTab.Text = "Objects";
            this.ObjectsTab.UseVisualStyleBackColor = true;
            // 
            // VariableGrid
            // 
            this.VariableGrid.AllowUserToAddRows = false;
            this.VariableGrid.AllowUserToDeleteRows = false;
            this.VariableGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.VariableGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.VariableName,
            this.Value});
            this.VariableGrid.Location = new System.Drawing.Point(12, 536);
            this.VariableGrid.Margin = new System.Windows.Forms.Padding(5, 5, 5, 5);
            this.VariableGrid.MultiSelect = false;
            this.VariableGrid.Name = "VariableGrid";
            this.VariableGrid.RowHeadersVisible = false;
            this.VariableGrid.RowHeadersWidth = 62;
            this.VariableGrid.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.VariableGrid.RowTemplate.Height = 28;
            this.VariableGrid.Size = new System.Drawing.Size(508, 333);
            this.VariableGrid.TabIndex = 13;
            this.VariableGrid.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.VariableGrid_CellValueChanged);
            // 
            // VariableName
            // 
            this.VariableName.HeaderText = "Name";
            this.VariableName.MinimumWidth = 8;
            this.VariableName.Name = "VariableName";
            this.VariableName.ReadOnly = true;
            this.VariableName.Width = 150;
            // 
            // Value
            // 
            this.Value.HeaderText = "Value";
            this.Value.MinimumWidth = 8;
            this.Value.Name = "Value";
            this.Value.Width = 127;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(18, 501);
            this.label3.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(134, 32);
            this.label3.TabIndex = 12;
            this.label3.Text = "Variables";
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
            this.label2.Size = new System.Drawing.Size(91, 32);
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
            this.TilesetTab.Size = new System.Drawing.Size(513, 1833);
            this.TilesetTab.TabIndex = 0;
            this.TilesetTab.Text = "Tileset";
            this.TilesetTab.UseVisualStyleBackColor = true;
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
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 19);
            this.label1.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(99, 32);
            this.label1.TabIndex = 4;
            this.label1.Text = "Tileset";
            // 
            // EditTab
            // 
            this.EditTab.Controls.Add(this.TilesetTab);
            this.EditTab.Controls.Add(this.ObjectsTab);
            this.EditTab.Controls.Add(this.Enemies);
            this.EditTab.Dock = System.Windows.Forms.DockStyle.Left;
            this.EditTab.Location = new System.Drawing.Point(0, 54);
            this.EditTab.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.EditTab.Name = "EditTab";
            this.EditTab.SelectedIndex = 0;
            this.EditTab.Size = new System.Drawing.Size(533, 1888);
            this.EditTab.TabIndex = 9;
            // 
            // vMapScroll
            // 
            this.vMapScroll.Dock = System.Windows.Forms.DockStyle.Right;
            this.vMapScroll.Location = new System.Drawing.Point(3347, 54);
            this.vMapScroll.Name = "vMapScroll";
            this.vMapScroll.Size = new System.Drawing.Size(20, 1908);
            this.vMapScroll.TabIndex = 7;
            this.vMapScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.VMapScroll_Scroll);
            // 
            // hMapScroll
            // 
            this.hMapScroll.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hMapScroll.Location = new System.Drawing.Point(0, 1942);
            this.hMapScroll.Name = "hMapScroll";
            this.hMapScroll.Size = new System.Drawing.Size(3347, 20);
            this.hMapScroll.TabIndex = 8;
            this.hMapScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.HMapScroll_Scroll);
            // 
            // MapEditor
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(3367, 1962);
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
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.MapContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.Map)).EndInit();
            this.Enemies.ResumeLayout(false);
            this.Enemies.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.EnemyPreviewPic)).EndInit();
            this.ObjectsTab.ResumeLayout(false);
            this.ObjectsTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ObjectTypePrevPic)).EndInit();
            this.TilesetTab.ResumeLayout(false);
            this.TilesetTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Tileset)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TilePreview)).EndInit();
            this.EditTab.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem quitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editorsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tilesetEditorToolStripMenuItem;
        private System.Windows.Forms.Panel MapContainer;
        private System.Windows.Forms.PictureBox Map;
        private System.Windows.Forms.ToolStripMenuItem gameObjectTypeEditorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mapSettingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem specialToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem createFrameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem animationEditorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem enemyTypeEditorToolStripMenuItem;
        private System.Windows.Forms.TabPage Enemies;
        private System.Windows.Forms.PictureBox EnemyPreviewPic;
        private System.Windows.Forms.Label EnemiesLabel;
        private System.Windows.Forms.ListBox EnemyList;
        private System.Windows.Forms.TabPage ObjectsTab;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.PictureBox ObjectTypePrevPic;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListBox GameObjectTypesList;
        private System.Windows.Forms.TabPage TilesetTab;
        private System.Windows.Forms.PictureBox Tileset;
        private System.Windows.Forms.PictureBox TilePreview;
        private System.Windows.Forms.ComboBox Tilesets;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TabControl EditTab;
        private System.Windows.Forms.DataGridView VariableGrid;
        private System.Windows.Forms.DataGridViewTextBoxColumn VariableName;
        private System.Windows.Forms.DataGridViewTextBoxColumn Value;
        private System.Windows.Forms.VScrollBar vMapScroll;
        private System.Windows.Forms.HScrollBar hMapScroll;
    }
}

