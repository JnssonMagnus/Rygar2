﻿namespace PlatformEditor
{
    partial class EnemyEditor
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
            this.IDText = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.SaveBtn = new System.Windows.Forms.Button();
            this.EnemiesTxt = new System.Windows.Forms.Label();
            this.NameText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.RemoveBtn = new System.Windows.Forms.Button();
            this.NewBtn = new System.Windows.Forms.Button();
            this.EnemyTypeList = new System.Windows.Forms.ListBox();
            this.LifeTxt = new System.Windows.Forms.Label();
            this.Life = new System.Windows.Forms.NumericUpDown();
            this.Staggered = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.enemyTabControl = new System.Windows.Forms.TabControl();
            this.enemyTab = new System.Windows.Forms.TabPage();
            this.physicsTab = new System.Windows.Forms.TabPage();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.Weight = new System.Windows.Forms.NumericUpDown();
            this.Bounciness = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.AirFrictionX = new System.Windows.Forms.NumericUpDown();
            this.RotationCheckbox = new System.Windows.Forms.CheckBox();
            this.GroundFrictionY = new System.Windows.Forms.NumericUpDown();
            this.KineticCheckbox = new System.Windows.Forms.CheckBox();
            this.label5 = new System.Windows.Forms.Label();
            this.GravityCheckbox = new System.Windows.Forms.CheckBox();
            this.label10 = new System.Windows.Forms.Label();
            this.PhysicsCheckbox = new System.Windows.Forms.CheckBox();
            this.AirFrictionY = new System.Windows.Forms.NumericUpDown();
            this.GroundFrictionX = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.variablesTab = new System.Windows.Forms.TabPage();
            this.VariableGrid = new System.Windows.Forms.DataGridView();
            this.VariableName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Value = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DefaultValueLabel = new System.Windows.Forms.Label();
            this.VariableDefaultValue = new System.Windows.Forms.NumericUpDown();
            this.VariableListBox = new System.Windows.Forms.ListBox();
            this.RenameVaribleBtn = new System.Windows.Forms.Button();
            this.RemoveVariableBtn = new System.Windows.Forms.Button();
            this.AddVaribleBtn = new System.Windows.Forms.Button();
            this.collisionTab = new System.Windows.Forms.TabPage();
            this.PickableTagCheckbox = new System.Windows.Forms.CheckBox();
            this.BulletTagCheckbox = new System.Windows.Forms.CheckBox();
            this.EnemyTagCheckbox = new System.Windows.Forms.CheckBox();
            this.PlayerTagCheckbox = new System.Windows.Forms.CheckBox();
            this.animationTab = new System.Windows.Forms.TabPage();
            this.ImageSizeText = new System.Windows.Forms.Label();
            this.ImageNameText = new System.Windows.Forms.Label();
            this.FPSLabel = new System.Windows.Forms.Label();
            this.FPSValue = new System.Windows.Forms.NumericUpDown();
            this.FramesLabel = new System.Windows.Forms.Label();
            this.FramesValue = new System.Windows.Forms.NumericUpDown();
            this.HeightLabel = new System.Windows.Forms.Label();
            this.WidthLabel = new System.Windows.Forms.Label();
            this.WidthValue = new System.Windows.Forms.NumericUpDown();
            this.HeightValue = new System.Windows.Forms.NumericUpDown();
            this.SelectedAnimation = new System.Windows.Forms.ListBox();
            this.SelectPicBtn = new System.Windows.Forms.Button();
            this.EnemyPic = new System.Windows.Forms.PictureBox();
            this.behaviorsTab = new System.Windows.Forms.TabPage();
            ((System.ComponentModel.ISupportInitialize)(this.Life)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Staggered)).BeginInit();
            this.enemyTabControl.SuspendLayout();
            this.enemyTab.SuspendLayout();
            this.physicsTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Weight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Bounciness)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionX)).BeginInit();
            this.variablesTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.VariableDefaultValue)).BeginInit();
            this.collisionTab.SuspendLayout();
            this.animationTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.FPSValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.FramesValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.WidthValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeightValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.EnemyPic)).BeginInit();
            this.SuspendLayout();
            // 
            // IDText
            // 
            this.IDText.AutoSize = true;
            this.IDText.Location = new System.Drawing.Point(213, 102);
            this.IDText.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.IDText.Name = "IDText";
            this.IDText.Size = new System.Drawing.Size(30, 32);
            this.IDText.TabIndex = 38;
            this.IDText.Text = "0";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(39, 102);
            this.label11.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(41, 32);
            this.label11.TabIndex = 37;
            this.label11.Text = "ID";
            // 
            // SaveBtn
            // 
            this.SaveBtn.Location = new System.Drawing.Point(46, 631);
            this.SaveBtn.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.SaveBtn.Name = "SaveBtn";
            this.SaveBtn.Size = new System.Drawing.Size(199, 54);
            this.SaveBtn.TabIndex = 36;
            this.SaveBtn.Text = "&Save";
            this.SaveBtn.UseVisualStyleBackColor = true;
            this.SaveBtn.Click += new System.EventHandler(this.SaveBtn_Click);
            // 
            // EnemiesTxt
            // 
            this.EnemiesTxt.AutoSize = true;
            this.EnemiesTxt.Location = new System.Drawing.Point(39, 45);
            this.EnemiesTxt.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.EnemiesTxt.Name = "EnemiesTxt";
            this.EnemiesTxt.Size = new System.Drawing.Size(125, 32);
            this.EnemiesTxt.TabIndex = 35;
            this.EnemiesTxt.Text = "Enemies";
            // 
            // NameText
            // 
            this.NameText.Location = new System.Drawing.Point(220, 147);
            this.NameText.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.NameText.Name = "NameText";
            this.NameText.Size = new System.Drawing.Size(240, 38);
            this.NameText.TabIndex = 34;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(39, 155);
            this.label1.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(89, 32);
            this.label1.TabIndex = 33;
            this.label1.Text = "Name";
            // 
            // RemoveBtn
            // 
            this.RemoveBtn.Location = new System.Drawing.Point(265, 561);
            this.RemoveBtn.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.RemoveBtn.Name = "RemoveBtn";
            this.RemoveBtn.Size = new System.Drawing.Size(199, 54);
            this.RemoveBtn.TabIndex = 32;
            this.RemoveBtn.Text = "&Remove";
            this.RemoveBtn.UseVisualStyleBackColor = true;
            this.RemoveBtn.Click += new System.EventHandler(this.RemoveBtn_Click);
            // 
            // NewBtn
            // 
            this.NewBtn.Location = new System.Drawing.Point(46, 561);
            this.NewBtn.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.NewBtn.Name = "NewBtn";
            this.NewBtn.Size = new System.Drawing.Size(199, 54);
            this.NewBtn.TabIndex = 31;
            this.NewBtn.Text = "&New";
            this.NewBtn.UseVisualStyleBackColor = true;
            this.NewBtn.Click += new System.EventHandler(this.NewBtn_Click);
            // 
            // EnemyTypeList
            // 
            this.EnemyTypeList.FormattingEnabled = true;
            this.EnemyTypeList.ItemHeight = 31;
            this.EnemyTypeList.Location = new System.Drawing.Point(46, 226);
            this.EnemyTypeList.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.EnemyTypeList.Name = "EnemyTypeList";
            this.EnemyTypeList.Size = new System.Drawing.Size(413, 314);
            this.EnemyTypeList.TabIndex = 30;
            this.EnemyTypeList.SelectedIndexChanged += new System.EventHandler(this.EnemyTypeList_SelectedIndexChanged);
            // 
            // LifeTxt
            // 
            this.LifeTxt.AutoSize = true;
            this.LifeTxt.Location = new System.Drawing.Point(32, 31);
            this.LifeTxt.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.LifeTxt.Name = "LifeTxt";
            this.LifeTxt.Size = new System.Drawing.Size(61, 32);
            this.LifeTxt.TabIndex = 39;
            this.LifeTxt.Text = "Life";
            // 
            // Life
            // 
            this.Life.DecimalPlaces = 2;
            this.Life.Location = new System.Drawing.Point(265, 28);
            this.Life.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.Life.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.Life.Name = "Life";
            this.Life.Size = new System.Drawing.Size(149, 38);
            this.Life.TabIndex = 40;
            this.Life.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Life.ValueChanged += new System.EventHandler(this.Life_ValueChanged);
            // 
            // Staggered
            // 
            this.Staggered.DecimalPlaces = 2;
            this.Staggered.Location = new System.Drawing.Point(265, 108);
            this.Staggered.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.Staggered.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.Staggered.Name = "Staggered";
            this.Staggered.Size = new System.Drawing.Size(149, 38);
            this.Staggered.TabIndex = 42;
            this.Staggered.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Staggered.ValueChanged += new System.EventHandler(this.Staggered_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(32, 112);
            this.label2.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(215, 32);
            this.label2.TabIndex = 41;
            this.label2.Text = "Staggered (sec)";
            // 
            // enemyTabControl
            // 
            this.enemyTabControl.Controls.Add(this.enemyTab);
            this.enemyTabControl.Controls.Add(this.physicsTab);
            this.enemyTabControl.Controls.Add(this.variablesTab);
            this.enemyTabControl.Controls.Add(this.collisionTab);
            this.enemyTabControl.Controls.Add(this.animationTab);
            this.enemyTabControl.Controls.Add(this.behaviorsTab);
            this.enemyTabControl.Location = new System.Drawing.Point(517, 45);
            this.enemyTabControl.Margin = new System.Windows.Forms.Padding(5);
            this.enemyTabControl.Name = "enemyTabControl";
            this.enemyTabControl.SelectedIndex = 0;
            this.enemyTabControl.Size = new System.Drawing.Size(1388, 946);
            this.enemyTabControl.TabIndex = 43;
            this.enemyTabControl.Visible = false;
            // 
            // enemyTab
            // 
            this.enemyTab.Controls.Add(this.label2);
            this.enemyTab.Controls.Add(this.Staggered);
            this.enemyTab.Controls.Add(this.LifeTxt);
            this.enemyTab.Controls.Add(this.Life);
            this.enemyTab.Location = new System.Drawing.Point(10, 48);
            this.enemyTab.Margin = new System.Windows.Forms.Padding(5);
            this.enemyTab.Name = "enemyTab";
            this.enemyTab.Size = new System.Drawing.Size(1368, 888);
            this.enemyTab.TabIndex = 3;
            this.enemyTab.Text = "EnemyData";
            this.enemyTab.UseVisualStyleBackColor = true;
            // 
            // physicsTab
            // 
            this.physicsTab.Controls.Add(this.label3);
            this.physicsTab.Controls.Add(this.label4);
            this.physicsTab.Controls.Add(this.Weight);
            this.physicsTab.Controls.Add(this.Bounciness);
            this.physicsTab.Controls.Add(this.label6);
            this.physicsTab.Controls.Add(this.label7);
            this.physicsTab.Controls.Add(this.label9);
            this.physicsTab.Controls.Add(this.AirFrictionX);
            this.physicsTab.Controls.Add(this.RotationCheckbox);
            this.physicsTab.Controls.Add(this.GroundFrictionY);
            this.physicsTab.Controls.Add(this.KineticCheckbox);
            this.physicsTab.Controls.Add(this.label5);
            this.physicsTab.Controls.Add(this.GravityCheckbox);
            this.physicsTab.Controls.Add(this.label10);
            this.physicsTab.Controls.Add(this.PhysicsCheckbox);
            this.physicsTab.Controls.Add(this.AirFrictionY);
            this.physicsTab.Controls.Add(this.GroundFrictionX);
            this.physicsTab.Controls.Add(this.label8);
            this.physicsTab.Location = new System.Drawing.Point(10, 48);
            this.physicsTab.Margin = new System.Windows.Forms.Padding(5);
            this.physicsTab.Name = "physicsTab";
            this.physicsTab.Padding = new System.Windows.Forms.Padding(5);
            this.physicsTab.Size = new System.Drawing.Size(1368, 888);
            this.physicsTab.TabIndex = 0;
            this.physicsTab.Text = "Physics";
            this.physicsTab.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(39, 36);
            this.label3.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(103, 32);
            this.label3.TabIndex = 7;
            this.label3.Text = "Weight";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(39, 98);
            this.label4.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(162, 32);
            this.label4.TabIndex = 6;
            this.label4.Text = "Bounciness";
            // 
            // Weight
            // 
            this.Weight.DecimalPlaces = 2;
            this.Weight.Location = new System.Drawing.Point(220, 36);
            this.Weight.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.Weight.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.Weight.Name = "Weight";
            this.Weight.Size = new System.Drawing.Size(149, 38);
            this.Weight.TabIndex = 15;
            this.Weight.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Weight.ValueChanged += new System.EventHandler(this.Weight_ValueChanged);
            // 
            // Bounciness
            // 
            this.Bounciness.DecimalPlaces = 3;
            this.Bounciness.Location = new System.Drawing.Point(220, 98);
            this.Bounciness.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.Bounciness.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Bounciness.Name = "Bounciness";
            this.Bounciness.Size = new System.Drawing.Size(149, 38);
            this.Bounciness.TabIndex = 16;
            this.Bounciness.Value = new decimal(new int[] {
            8,
            0,
            0,
            65536});
            this.Bounciness.ValueChanged += new System.EventHandler(this.Bounciness_ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(39, 167);
            this.label6.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(150, 32);
            this.label6.TabIndex = 17;
            this.label6.Text = "Air Friction";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(39, 363);
            this.label7.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(210, 32);
            this.label7.TabIndex = 18;
            this.label7.Text = "Ground Friction";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(151, 468);
            this.label9.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(33, 32);
            this.label9.TabIndex = 26;
            this.label9.Text = "Y";
            // 
            // AirFrictionX
            // 
            this.AirFrictionX.DecimalPlaces = 2;
            this.AirFrictionX.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.AirFrictionX.Location = new System.Drawing.Point(220, 200);
            this.AirFrictionX.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.AirFrictionX.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionX.Name = "AirFrictionX";
            this.AirFrictionX.Size = new System.Drawing.Size(149, 38);
            this.AirFrictionX.TabIndex = 19;
            this.AirFrictionX.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionX.ValueChanged += new System.EventHandler(this.AirFrictionX_ValueChanged);
            // 
            // RotationCheckbox
            // 
            this.RotationCheckbox.AutoSize = true;
            this.RotationCheckbox.Location = new System.Drawing.Point(455, 206);
            this.RotationCheckbox.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.RotationCheckbox.Name = "RotationCheckbox";
            this.RotationCheckbox.Size = new System.Drawing.Size(225, 36);
            this.RotationCheckbox.TabIndex = 11;
            this.RotationCheckbox.Text = "Auto Rotation";
            this.RotationCheckbox.UseVisualStyleBackColor = true;
            this.RotationCheckbox.CheckedChanged += new System.EventHandler(this.RotationCheckbox_CheckedChanged);
            // 
            // GroundFrictionY
            // 
            this.GroundFrictionY.DecimalPlaces = 2;
            this.GroundFrictionY.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.GroundFrictionY.Location = new System.Drawing.Point(220, 463);
            this.GroundFrictionY.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.GroundFrictionY.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionY.Name = "GroundFrictionY";
            this.GroundFrictionY.Size = new System.Drawing.Size(149, 38);
            this.GroundFrictionY.TabIndex = 25;
            this.GroundFrictionY.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionY.ValueChanged += new System.EventHandler(this.GroundFrictionY_ValueChanged);
            // 
            // KineticCheckbox
            // 
            this.KineticCheckbox.AutoSize = true;
            this.KineticCheckbox.Location = new System.Drawing.Point(455, 149);
            this.KineticCheckbox.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.KineticCheckbox.Name = "KineticCheckbox";
            this.KineticCheckbox.Size = new System.Drawing.Size(139, 36);
            this.KineticCheckbox.TabIndex = 10;
            this.KineticCheckbox.Text = "Kinetic";
            this.KineticCheckbox.UseVisualStyleBackColor = true;
            this.KineticCheckbox.CheckedChanged += new System.EventHandler(this.KineticCheckbox_CheckedChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(151, 205);
            this.label5.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(33, 32);
            this.label5.TabIndex = 20;
            this.label5.Text = "X";
            // 
            // GravityCheckbox
            // 
            this.GravityCheckbox.AutoSize = true;
            this.GravityCheckbox.Location = new System.Drawing.Point(455, 91);
            this.GravityCheckbox.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.GravityCheckbox.Name = "GravityCheckbox";
            this.GravityCheckbox.Size = new System.Drawing.Size(142, 36);
            this.GravityCheckbox.TabIndex = 9;
            this.GravityCheckbox.Text = "Gravity";
            this.GravityCheckbox.UseVisualStyleBackColor = true;
            this.GravityCheckbox.CheckedChanged += new System.EventHandler(this.GravityCheckbox_CheckedChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(151, 406);
            this.label10.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(33, 32);
            this.label10.TabIndex = 24;
            this.label10.Text = "X";
            // 
            // PhysicsCheckbox
            // 
            this.PhysicsCheckbox.AutoSize = true;
            this.PhysicsCheckbox.Location = new System.Drawing.Point(455, 34);
            this.PhysicsCheckbox.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.PhysicsCheckbox.Name = "PhysicsCheckbox";
            this.PhysicsCheckbox.Size = new System.Drawing.Size(260, 36);
            this.PhysicsCheckbox.TabIndex = 8;
            this.PhysicsCheckbox.Text = "Physics enabled";
            this.PhysicsCheckbox.UseVisualStyleBackColor = true;
            this.PhysicsCheckbox.CheckedChanged += new System.EventHandler(this.PhysicsCheckbox_CheckedChanged);
            // 
            // AirFrictionY
            // 
            this.AirFrictionY.DecimalPlaces = 2;
            this.AirFrictionY.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.AirFrictionY.Location = new System.Drawing.Point(220, 262);
            this.AirFrictionY.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.AirFrictionY.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionY.Name = "AirFrictionY";
            this.AirFrictionY.Size = new System.Drawing.Size(149, 38);
            this.AirFrictionY.TabIndex = 21;
            this.AirFrictionY.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionY.ValueChanged += new System.EventHandler(this.AirFrictionY_ValueChanged);
            // 
            // GroundFrictionX
            // 
            this.GroundFrictionX.DecimalPlaces = 2;
            this.GroundFrictionX.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.GroundFrictionX.Location = new System.Drawing.Point(220, 401);
            this.GroundFrictionX.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.GroundFrictionX.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionX.Name = "GroundFrictionX";
            this.GroundFrictionX.Size = new System.Drawing.Size(149, 38);
            this.GroundFrictionX.TabIndex = 23;
            this.GroundFrictionX.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionX.ValueChanged += new System.EventHandler(this.GroundFrictionX_ValueChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(151, 267);
            this.label8.Margin = new System.Windows.Forms.Padding(7, 0, 7, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(33, 32);
            this.label8.TabIndex = 22;
            this.label8.Text = "Y";
            // 
            // variablesTab
            // 
            this.variablesTab.Controls.Add(this.VariableGrid);
            this.variablesTab.Controls.Add(this.DefaultValueLabel);
            this.variablesTab.Controls.Add(this.VariableDefaultValue);
            this.variablesTab.Controls.Add(this.VariableListBox);
            this.variablesTab.Controls.Add(this.RenameVaribleBtn);
            this.variablesTab.Controls.Add(this.RemoveVariableBtn);
            this.variablesTab.Controls.Add(this.AddVaribleBtn);
            this.variablesTab.Location = new System.Drawing.Point(10, 48);
            this.variablesTab.Margin = new System.Windows.Forms.Padding(5);
            this.variablesTab.Name = "variablesTab";
            this.variablesTab.Padding = new System.Windows.Forms.Padding(5);
            this.variablesTab.Size = new System.Drawing.Size(1368, 888);
            this.variablesTab.TabIndex = 1;
            this.variablesTab.Text = "Variables";
            this.variablesTab.UseVisualStyleBackColor = true;
            // 
            // VariableGrid
            // 
            this.VariableGrid.AllowUserToAddRows = false;
            this.VariableGrid.AllowUserToDeleteRows = false;
            this.VariableGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.VariableGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.VariableName,
            this.Value});
            this.VariableGrid.Location = new System.Drawing.Point(34, 42);
            this.VariableGrid.Margin = new System.Windows.Forms.Padding(5);
            this.VariableGrid.MultiSelect = false;
            this.VariableGrid.Name = "VariableGrid";
            this.VariableGrid.RowHeadersVisible = false;
            this.VariableGrid.RowHeadersWidth = 62;
            this.VariableGrid.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.VariableGrid.RowTemplate.Height = 28;
            this.VariableGrid.Size = new System.Drawing.Size(564, 333);
            this.VariableGrid.TabIndex = 6;
            // 
            // VariableName
            // 
            this.VariableName.HeaderText = "Name";
            this.VariableName.MinimumWidth = 8;
            this.VariableName.Name = "VariableName";
            this.VariableName.Width = 150;
            // 
            // Value
            // 
            this.Value.HeaderText = "Default";
            this.Value.MinimumWidth = 8;
            this.Value.Name = "Value";
            this.Value.Width = 150;
            // 
            // DefaultValueLabel
            // 
            this.DefaultValueLabel.AutoSize = true;
            this.DefaultValueLabel.Location = new System.Drawing.Point(478, 42);
            this.DefaultValueLabel.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.DefaultValueLabel.Name = "DefaultValueLabel";
            this.DefaultValueLabel.Size = new System.Drawing.Size(181, 32);
            this.DefaultValueLabel.TabIndex = 5;
            this.DefaultValueLabel.Text = "Default value";
            // 
            // VariableDefaultValue
            // 
            this.VariableDefaultValue.DecimalPlaces = 2;
            this.VariableDefaultValue.Location = new System.Drawing.Point(485, 78);
            this.VariableDefaultValue.Margin = new System.Windows.Forms.Padding(5);
            this.VariableDefaultValue.Name = "VariableDefaultValue";
            this.VariableDefaultValue.Size = new System.Drawing.Size(213, 38);
            this.VariableDefaultValue.TabIndex = 4;
            // 
            // VariableListBox
            // 
            this.VariableListBox.FormattingEnabled = true;
            this.VariableListBox.ItemHeight = 31;
            this.VariableListBox.Location = new System.Drawing.Point(565, -31);
            this.VariableListBox.Margin = new System.Windows.Forms.Padding(5);
            this.VariableListBox.Name = "VariableListBox";
            this.VariableListBox.Size = new System.Drawing.Size(400, 221);
            this.VariableListBox.TabIndex = 3;
            // 
            // RenameVaribleBtn
            // 
            this.RenameVaribleBtn.Location = new System.Drawing.Point(453, 443);
            this.RenameVaribleBtn.Margin = new System.Windows.Forms.Padding(5);
            this.RenameVaribleBtn.Name = "RenameVaribleBtn";
            this.RenameVaribleBtn.Size = new System.Drawing.Size(164, 54);
            this.RenameVaribleBtn.TabIndex = 2;
            this.RenameVaribleBtn.Text = "Rename";
            this.RenameVaribleBtn.UseVisualStyleBackColor = true;
            // 
            // RemoveVariableBtn
            // 
            this.RemoveVariableBtn.Location = new System.Drawing.Point(215, 443);
            this.RemoveVariableBtn.Margin = new System.Windows.Forms.Padding(5);
            this.RemoveVariableBtn.Name = "RemoveVariableBtn";
            this.RemoveVariableBtn.Size = new System.Drawing.Size(164, 54);
            this.RemoveVariableBtn.TabIndex = 1;
            this.RemoveVariableBtn.Text = "&Remove";
            this.RemoveVariableBtn.UseVisualStyleBackColor = true;
            // 
            // AddVaribleBtn
            // 
            this.AddVaribleBtn.Location = new System.Drawing.Point(11, 443);
            this.AddVaribleBtn.Margin = new System.Windows.Forms.Padding(5);
            this.AddVaribleBtn.Name = "AddVaribleBtn";
            this.AddVaribleBtn.Size = new System.Drawing.Size(164, 53);
            this.AddVaribleBtn.TabIndex = 0;
            this.AddVaribleBtn.Text = "&Add";
            this.AddVaribleBtn.UseVisualStyleBackColor = true;
            // 
            // collisionTab
            // 
            this.collisionTab.Controls.Add(this.PickableTagCheckbox);
            this.collisionTab.Controls.Add(this.BulletTagCheckbox);
            this.collisionTab.Controls.Add(this.EnemyTagCheckbox);
            this.collisionTab.Controls.Add(this.PlayerTagCheckbox);
            this.collisionTab.Location = new System.Drawing.Point(10, 48);
            this.collisionTab.Margin = new System.Windows.Forms.Padding(5);
            this.collisionTab.Name = "collisionTab";
            this.collisionTab.Size = new System.Drawing.Size(1368, 888);
            this.collisionTab.TabIndex = 2;
            this.collisionTab.Text = "Collision tags";
            this.collisionTab.UseVisualStyleBackColor = true;
            // 
            // PickableTagCheckbox
            // 
            this.PickableTagCheckbox.AutoSize = true;
            this.PickableTagCheckbox.Location = new System.Drawing.Point(43, 195);
            this.PickableTagCheckbox.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.PickableTagCheckbox.Name = "PickableTagCheckbox";
            this.PickableTagCheckbox.Size = new System.Drawing.Size(161, 36);
            this.PickableTagCheckbox.TabIndex = 33;
            this.PickableTagCheckbox.Text = "&Pickable";
            this.PickableTagCheckbox.UseVisualStyleBackColor = true;
            this.PickableTagCheckbox.CheckedChanged += new System.EventHandler(this.PickableTagCheckbox_CheckedChanged);
            // 
            // BulletTagCheckbox
            // 
            this.BulletTagCheckbox.AutoSize = true;
            this.BulletTagCheckbox.Location = new System.Drawing.Point(43, 141);
            this.BulletTagCheckbox.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.BulletTagCheckbox.Name = "BulletTagCheckbox";
            this.BulletTagCheckbox.Size = new System.Drawing.Size(125, 36);
            this.BulletTagCheckbox.TabIndex = 32;
            this.BulletTagCheckbox.Text = "&Bullet";
            this.BulletTagCheckbox.UseVisualStyleBackColor = true;
            this.BulletTagCheckbox.CheckedChanged += new System.EventHandler(this.BulletTagCheckbox_CheckedChanged);
            // 
            // EnemyTagCheckbox
            // 
            this.EnemyTagCheckbox.AutoSize = true;
            this.EnemyTagCheckbox.Location = new System.Drawing.Point(43, 31);
            this.EnemyTagCheckbox.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.EnemyTagCheckbox.Name = "EnemyTagCheckbox";
            this.EnemyTagCheckbox.Size = new System.Drawing.Size(140, 36);
            this.EnemyTagCheckbox.TabIndex = 30;
            this.EnemyTagCheckbox.Text = "Enemy";
            this.EnemyTagCheckbox.UseVisualStyleBackColor = true;
            this.EnemyTagCheckbox.CheckedChanged += new System.EventHandler(this.EnemyTagCheckbox_CheckedChanged);
            // 
            // PlayerTagCheckbox
            // 
            this.PlayerTagCheckbox.AutoSize = true;
            this.PlayerTagCheckbox.Location = new System.Drawing.Point(43, 85);
            this.PlayerTagCheckbox.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.PlayerTagCheckbox.Name = "PlayerTagCheckbox";
            this.PlayerTagCheckbox.Size = new System.Drawing.Size(133, 36);
            this.PlayerTagCheckbox.TabIndex = 31;
            this.PlayerTagCheckbox.Text = "Player";
            this.PlayerTagCheckbox.UseVisualStyleBackColor = true;
            this.PlayerTagCheckbox.CheckedChanged += new System.EventHandler(this.PlayerTagCheckbox_CheckedChanged);
            // 
            // animationTab
            // 
            this.animationTab.Controls.Add(this.ImageSizeText);
            this.animationTab.Controls.Add(this.ImageNameText);
            this.animationTab.Controls.Add(this.FPSLabel);
            this.animationTab.Controls.Add(this.FPSValue);
            this.animationTab.Controls.Add(this.FramesLabel);
            this.animationTab.Controls.Add(this.FramesValue);
            this.animationTab.Controls.Add(this.HeightLabel);
            this.animationTab.Controls.Add(this.WidthLabel);
            this.animationTab.Controls.Add(this.WidthValue);
            this.animationTab.Controls.Add(this.HeightValue);
            this.animationTab.Controls.Add(this.SelectedAnimation);
            this.animationTab.Controls.Add(this.SelectPicBtn);
            this.animationTab.Controls.Add(this.EnemyPic);
            this.animationTab.Location = new System.Drawing.Point(10, 48);
            this.animationTab.Margin = new System.Windows.Forms.Padding(5);
            this.animationTab.Name = "animationTab";
            this.animationTab.Size = new System.Drawing.Size(1368, 888);
            this.animationTab.TabIndex = 4;
            this.animationTab.Text = "Animations";
            this.animationTab.UseVisualStyleBackColor = true;
            // 
            // ImageSizeText
            // 
            this.ImageSizeText.AutoSize = true;
            this.ImageSizeText.Location = new System.Drawing.Point(21, 240);
            this.ImageSizeText.Name = "ImageSizeText";
            this.ImageSizeText.Size = new System.Drawing.Size(0, 32);
            this.ImageSizeText.TabIndex = 50;
            // 
            // ImageNameText
            // 
            this.ImageNameText.AutoSize = true;
            this.ImageNameText.Location = new System.Drawing.Point(21, 195);
            this.ImageNameText.Name = "ImageNameText";
            this.ImageNameText.Size = new System.Drawing.Size(0, 32);
            this.ImageNameText.TabIndex = 49;
            // 
            // FPSLabel
            // 
            this.FPSLabel.AutoSize = true;
            this.FPSLabel.Location = new System.Drawing.Point(372, 112);
            this.FPSLabel.Name = "FPSLabel";
            this.FPSLabel.Size = new System.Drawing.Size(69, 32);
            this.FPSLabel.TabIndex = 48;
            this.FPSLabel.Text = "FPS";
            // 
            // FPSValue
            // 
            this.FPSValue.Location = new System.Drawing.Point(510, 112);
            this.FPSValue.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.FPSValue.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.FPSValue.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.FPSValue.Name = "FPSValue";
            this.FPSValue.Size = new System.Drawing.Size(149, 38);
            this.FPSValue.TabIndex = 47;
            this.FPSValue.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.FPSValue.ValueChanged += new System.EventHandler(this.FPSValue_ValueChanged);
            // 
            // FramesLabel
            // 
            this.FramesLabel.AutoSize = true;
            this.FramesLabel.Location = new System.Drawing.Point(372, 34);
            this.FramesLabel.Name = "FramesLabel";
            this.FramesLabel.Size = new System.Drawing.Size(109, 32);
            this.FramesLabel.TabIndex = 46;
            this.FramesLabel.Text = "Frames";
            // 
            // FramesValue
            // 
            this.FramesValue.Location = new System.Drawing.Point(510, 34);
            this.FramesValue.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.FramesValue.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.FramesValue.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.FramesValue.Name = "FramesValue";
            this.FramesValue.Size = new System.Drawing.Size(149, 38);
            this.FramesValue.TabIndex = 45;
            this.FramesValue.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.FramesValue.ValueChanged += new System.EventHandler(this.FramesValue_ValueChanged);
            // 
            // HeightLabel
            // 
            this.HeightLabel.AutoSize = true;
            this.HeightLabel.Location = new System.Drawing.Point(21, 106);
            this.HeightLabel.Name = "HeightLabel";
            this.HeightLabel.Size = new System.Drawing.Size(97, 32);
            this.HeightLabel.TabIndex = 44;
            this.HeightLabel.Text = "Height";
            // 
            // WidthLabel
            // 
            this.WidthLabel.AutoSize = true;
            this.WidthLabel.Location = new System.Drawing.Point(21, 40);
            this.WidthLabel.Name = "WidthLabel";
            this.WidthLabel.Size = new System.Drawing.Size(87, 32);
            this.WidthLabel.TabIndex = 43;
            this.WidthLabel.Text = "Width";
            this.WidthLabel.Click += new System.EventHandler(this.label12_Click);
            // 
            // WidthValue
            // 
            this.WidthValue.Location = new System.Drawing.Point(159, 35);
            this.WidthValue.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.WidthValue.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.WidthValue.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.WidthValue.Name = "WidthValue";
            this.WidthValue.Size = new System.Drawing.Size(149, 38);
            this.WidthValue.TabIndex = 42;
            this.WidthValue.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.WidthValue.ValueChanged += new System.EventHandler(this.WidthValue_ValueChanged);
            // 
            // HeightValue
            // 
            this.HeightValue.Location = new System.Drawing.Point(159, 106);
            this.HeightValue.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.HeightValue.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.HeightValue.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.HeightValue.Name = "HeightValue";
            this.HeightValue.Size = new System.Drawing.Size(149, 38);
            this.HeightValue.TabIndex = 41;
            this.HeightValue.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.HeightValue.ValueChanged += new System.EventHandler(this.HeightValue_ValueChanged);
            // 
            // SelectedAnimation
            // 
            this.SelectedAnimation.FormattingEnabled = true;
            this.SelectedAnimation.ItemHeight = 31;
            this.SelectedAnimation.Items.AddRange(new object[] {
            "Default",
            "Idle",
            "Walk",
            "Dead",
            "Fall",
            "Jump"});
            this.SelectedAnimation.Location = new System.Drawing.Point(728, 34);
            this.SelectedAnimation.Margin = new System.Windows.Forms.Padding(5);
            this.SelectedAnimation.Name = "SelectedAnimation";
            this.SelectedAnimation.Size = new System.Drawing.Size(210, 190);
            this.SelectedAnimation.TabIndex = 8;
            this.SelectedAnimation.SelectedIndexChanged += new System.EventHandler(this.SelectedAnimation_SelectedIndexChanged);
            // 
            // SelectPicBtn
            // 
            this.SelectPicBtn.Location = new System.Drawing.Point(25, 294);
            this.SelectPicBtn.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.SelectPicBtn.Name = "SelectPicBtn";
            this.SelectPicBtn.Size = new System.Drawing.Size(71, 54);
            this.SelectPicBtn.TabIndex = 7;
            this.SelectPicBtn.Text = "..";
            this.SelectPicBtn.UseVisualStyleBackColor = true;
            this.SelectPicBtn.Click += new System.EventHandler(this.SelectPicBtn_Click);
            // 
            // EnemyPic
            // 
            this.EnemyPic.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.EnemyPic.Location = new System.Drawing.Point(110, 294);
            this.EnemyPic.Margin = new System.Windows.Forms.Padding(7, 8, 7, 8);
            this.EnemyPic.Name = "EnemyPic";
            this.EnemyPic.Size = new System.Drawing.Size(263, 236);
            this.EnemyPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.EnemyPic.TabIndex = 6;
            this.EnemyPic.TabStop = false;
            this.EnemyPic.Click += new System.EventHandler(this.EnemyPic_Click);
            this.EnemyPic.Paint += new System.Windows.Forms.PaintEventHandler(this.EnemyPic_Paint);
            // 
            // behaviorsTab
            // 
            this.behaviorsTab.Location = new System.Drawing.Point(10, 48);
            this.behaviorsTab.Margin = new System.Windows.Forms.Padding(5);
            this.behaviorsTab.Name = "behaviorsTab";
            this.behaviorsTab.Size = new System.Drawing.Size(1368, 888);
            this.behaviorsTab.TabIndex = 5;
            this.behaviorsTab.Text = "Behaviors";
            this.behaviorsTab.UseVisualStyleBackColor = true;
            // 
            // EnemyEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(2133, 1313);
            this.Controls.Add(this.enemyTabControl);
            this.Controls.Add(this.IDText);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.SaveBtn);
            this.Controls.Add(this.EnemiesTxt);
            this.Controls.Add(this.NameText);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.RemoveBtn);
            this.Controls.Add(this.NewBtn);
            this.Controls.Add(this.EnemyTypeList);
            this.Margin = new System.Windows.Forms.Padding(5);
            this.Name = "EnemyEditor";
            this.Text = "EnemyEditor";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.EnemyEditor_FormClosed);
            this.Load += new System.EventHandler(this.EnemyEditor_Load);
            ((System.ComponentModel.ISupportInitialize)(this.Life)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Staggered)).EndInit();
            this.enemyTabControl.ResumeLayout(false);
            this.enemyTab.ResumeLayout(false);
            this.enemyTab.PerformLayout();
            this.physicsTab.ResumeLayout(false);
            this.physicsTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Weight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Bounciness)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionX)).EndInit();
            this.variablesTab.ResumeLayout(false);
            this.variablesTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.VariableDefaultValue)).EndInit();
            this.collisionTab.ResumeLayout(false);
            this.collisionTab.PerformLayout();
            this.animationTab.ResumeLayout(false);
            this.animationTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.FPSValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.FramesValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.WidthValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeightValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.EnemyPic)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label IDText;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button SaveBtn;
        private System.Windows.Forms.Label EnemiesTxt;
        private System.Windows.Forms.TextBox NameText;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button RemoveBtn;
        private System.Windows.Forms.Button NewBtn;
        private System.Windows.Forms.ListBox EnemyTypeList;
        private System.Windows.Forms.Label LifeTxt;
        private System.Windows.Forms.NumericUpDown Life;
        private System.Windows.Forms.NumericUpDown Staggered;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TabControl enemyTabControl;
        private System.Windows.Forms.TabPage enemyTab;
        private System.Windows.Forms.TabPage physicsTab;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown Weight;
        private System.Windows.Forms.NumericUpDown Bounciness;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.NumericUpDown AirFrictionX;
        private System.Windows.Forms.CheckBox RotationCheckbox;
        private System.Windows.Forms.NumericUpDown GroundFrictionY;
        private System.Windows.Forms.CheckBox KineticCheckbox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.CheckBox GravityCheckbox;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckBox PhysicsCheckbox;
        private System.Windows.Forms.NumericUpDown AirFrictionY;
        private System.Windows.Forms.NumericUpDown GroundFrictionX;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TabPage variablesTab;
        private System.Windows.Forms.DataGridView VariableGrid;
        private System.Windows.Forms.DataGridViewTextBoxColumn VariableName;
        private System.Windows.Forms.DataGridViewTextBoxColumn Value;
        private System.Windows.Forms.Label DefaultValueLabel;
        private System.Windows.Forms.NumericUpDown VariableDefaultValue;
        private System.Windows.Forms.ListBox VariableListBox;
        private System.Windows.Forms.Button RenameVaribleBtn;
        private System.Windows.Forms.Button RemoveVariableBtn;
        private System.Windows.Forms.Button AddVaribleBtn;
        private System.Windows.Forms.TabPage collisionTab;
        private System.Windows.Forms.CheckBox PickableTagCheckbox;
        private System.Windows.Forms.CheckBox BulletTagCheckbox;
        private System.Windows.Forms.CheckBox EnemyTagCheckbox;
        private System.Windows.Forms.CheckBox PlayerTagCheckbox;
        private System.Windows.Forms.TabPage animationTab;
        private System.Windows.Forms.TabPage behaviorsTab;
        private System.Windows.Forms.Button SelectPicBtn;
        private System.Windows.Forms.PictureBox EnemyPic;
        private System.Windows.Forms.ListBox SelectedAnimation;
        private System.Windows.Forms.NumericUpDown HeightValue;
        private System.Windows.Forms.NumericUpDown WidthValue;
        private System.Windows.Forms.Label WidthLabel;
        private System.Windows.Forms.Label FPSLabel;
        private System.Windows.Forms.NumericUpDown FPSValue;
        private System.Windows.Forms.Label FramesLabel;
        private System.Windows.Forms.NumericUpDown FramesValue;
        private System.Windows.Forms.Label HeightLabel;
        private System.Windows.Forms.Label ImageSizeText;
        private System.Windows.Forms.Label ImageNameText;
    }
}