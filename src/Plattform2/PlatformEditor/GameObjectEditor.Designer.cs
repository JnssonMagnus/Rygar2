namespace PlatformEditor
{
    partial class GameObjectEditor
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
            this.GameObjectTypeList = new System.Windows.Forms.ListBox();
            this.NewBtn = new System.Windows.Forms.Button();
            this.RemoveBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.GameObjectPic = new System.Windows.Forms.PictureBox();
            this.SelectPicBtn = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.PhysicsCheckbox = new System.Windows.Forms.CheckBox();
            this.GravityCheckbox = new System.Windows.Forms.CheckBox();
            this.KineticCheckbox = new System.Windows.Forms.CheckBox();
            this.RotationCheckbox = new System.Windows.Forms.CheckBox();
            this.NameText = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.Weight = new System.Windows.Forms.NumericUpDown();
            this.Bounciness = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.AirFrictionX = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.AirFrictionY = new System.Windows.Forms.NumericUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.GroundFrictionY = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.GroundFrictionX = new System.Windows.Forms.NumericUpDown();
            this.SaveBtn = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.IDText = new System.Windows.Forms.Label();
            this.EnemyTagCheckbox = new System.Windows.Forms.CheckBox();
            this.PickableTagCheckbox = new System.Windows.Forms.CheckBox();
            this.BulletTagCheckbox = new System.Windows.Forms.CheckBox();
            this.PlayerTagCheckbox = new System.Windows.Forms.CheckBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.VariableGrid = new System.Windows.Forms.DataGridView();
            this.VariableName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Value = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DefaultValueLabel = new System.Windows.Forms.Label();
            this.VariableDefaultValue = new System.Windows.Forms.NumericUpDown();
            this.VariableListBox = new System.Windows.Forms.ListBox();
            this.RenameVaribleBtn = new System.Windows.Forms.Button();
            this.RemoveVariableBtn = new System.Windows.Forms.Button();
            this.AddVaribleBtn = new System.Windows.Forms.Button();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            ((System.ComponentModel.ISupportInitialize)(this.GameObjectPic)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Weight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Bounciness)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionX)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.VariableDefaultValue)).BeginInit();
            this.tabPage3.SuspendLayout();
            this.SuspendLayout();
            // 
            // GameObjectTypeList
            // 
            this.GameObjectTypeList.FormattingEnabled = true;
            this.GameObjectTypeList.ItemHeight = 20;
            this.GameObjectTypeList.Location = new System.Drawing.Point(18, 58);
            this.GameObjectTypeList.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GameObjectTypeList.Name = "GameObjectTypeList";
            this.GameObjectTypeList.Size = new System.Drawing.Size(234, 204);
            this.GameObjectTypeList.TabIndex = 0;
            this.GameObjectTypeList.SelectedIndexChanged += new System.EventHandler(this.GameObjectTypeList_SelectedIndexChanged);
            // 
            // NewBtn
            // 
            this.NewBtn.Location = new System.Drawing.Point(18, 274);
            this.NewBtn.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.NewBtn.Name = "NewBtn";
            this.NewBtn.Size = new System.Drawing.Size(112, 35);
            this.NewBtn.TabIndex = 1;
            this.NewBtn.Text = "&New";
            this.NewBtn.UseVisualStyleBackColor = true;
            this.NewBtn.Click += new System.EventHandler(this.NewBtn_Click);
            // 
            // RemoveBtn
            // 
            this.RemoveBtn.Location = new System.Drawing.Point(141, 274);
            this.RemoveBtn.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.RemoveBtn.Name = "RemoveBtn";
            this.RemoveBtn.Size = new System.Drawing.Size(112, 35);
            this.RemoveBtn.TabIndex = 2;
            this.RemoveBtn.Text = "&Remove";
            this.RemoveBtn.UseVisualStyleBackColor = true;
            this.RemoveBtn.Click += new System.EventHandler(this.RemoveBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(282, 63);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 20);
            this.label1.TabIndex = 3;
            this.label1.Text = "Name";
            // 
            // GameObjectPic
            // 
            this.GameObjectPic.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.GameObjectPic.Location = new System.Drawing.Point(754, 140);
            this.GameObjectPic.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GameObjectPic.Name = "GameObjectPic";
            this.GameObjectPic.Size = new System.Drawing.Size(149, 153);
            this.GameObjectPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.GameObjectPic.TabIndex = 4;
            this.GameObjectPic.TabStop = false;
            this.GameObjectPic.Click += new System.EventHandler(this.GameObjectPic_Click);
            // 
            // SelectPicBtn
            // 
            this.SelectPicBtn.Location = new System.Drawing.Point(864, 303);
            this.SelectPicBtn.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SelectPicBtn.Name = "SelectPicBtn";
            this.SelectPicBtn.Size = new System.Drawing.Size(40, 35);
            this.SelectPicBtn.TabIndex = 5;
            this.SelectPicBtn.Text = "..";
            this.SelectPicBtn.UseVisualStyleBackColor = true;
            this.SelectPicBtn.Click += new System.EventHandler(this.SelectPicBtn_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(22, 63);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(92, 20);
            this.label2.TabIndex = 6;
            this.label2.Text = "Bounciness";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(22, 23);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 20);
            this.label3.TabIndex = 7;
            this.label3.Text = "Weight";
            // 
            // PhysicsCheckbox
            // 
            this.PhysicsCheckbox.AutoSize = true;
            this.PhysicsCheckbox.Location = new System.Drawing.Point(256, 22);
            this.PhysicsCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.PhysicsCheckbox.Name = "PhysicsCheckbox";
            this.PhysicsCheckbox.Size = new System.Drawing.Size(149, 24);
            this.PhysicsCheckbox.TabIndex = 8;
            this.PhysicsCheckbox.Text = "Physics enabled";
            this.PhysicsCheckbox.UseVisualStyleBackColor = true;
            this.PhysicsCheckbox.CheckedChanged += new System.EventHandler(this.PhysicsCheckbox_CheckedChanged);
            // 
            // GravityCheckbox
            // 
            this.GravityCheckbox.AutoSize = true;
            this.GravityCheckbox.Location = new System.Drawing.Point(256, 59);
            this.GravityCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GravityCheckbox.Name = "GravityCheckbox";
            this.GravityCheckbox.Size = new System.Drawing.Size(84, 24);
            this.GravityCheckbox.TabIndex = 9;
            this.GravityCheckbox.Text = "Gravity";
            this.GravityCheckbox.UseVisualStyleBackColor = true;
            this.GravityCheckbox.CheckedChanged += new System.EventHandler(this.GravityCheckbox_CheckedChanged);
            // 
            // KineticCheckbox
            // 
            this.KineticCheckbox.AutoSize = true;
            this.KineticCheckbox.Location = new System.Drawing.Point(256, 96);
            this.KineticCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.KineticCheckbox.Name = "KineticCheckbox";
            this.KineticCheckbox.Size = new System.Drawing.Size(82, 24);
            this.KineticCheckbox.TabIndex = 10;
            this.KineticCheckbox.Text = "Kinetic";
            this.KineticCheckbox.UseVisualStyleBackColor = true;
            this.KineticCheckbox.CheckedChanged += new System.EventHandler(this.KineticCheckbox_CheckedChanged);
            // 
            // RotationCheckbox
            // 
            this.RotationCheckbox.AutoSize = true;
            this.RotationCheckbox.Location = new System.Drawing.Point(256, 133);
            this.RotationCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.RotationCheckbox.Name = "RotationCheckbox";
            this.RotationCheckbox.Size = new System.Drawing.Size(134, 24);
            this.RotationCheckbox.TabIndex = 11;
            this.RotationCheckbox.Text = "Auto Rotation";
            this.RotationCheckbox.UseVisualStyleBackColor = true;
            this.RotationCheckbox.CheckedChanged += new System.EventHandler(this.RotationCheckbox_CheckedChanged);
            // 
            // NameText
            // 
            this.NameText.Location = new System.Drawing.Point(384, 58);
            this.NameText.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.NameText.Name = "NameText";
            this.NameText.Size = new System.Drawing.Size(169, 26);
            this.NameText.TabIndex = 12;
            this.NameText.TextChanged += new System.EventHandler(this.NameText_TextChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(18, 29);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(149, 20);
            this.label5.TabIndex = 14;
            this.label5.Text = "Game Object Types";
            // 
            // Weight
            // 
            this.Weight.DecimalPlaces = 2;
            this.Weight.Location = new System.Drawing.Point(124, 23);
            this.Weight.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Weight.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.Weight.Name = "Weight";
            this.Weight.Size = new System.Drawing.Size(84, 26);
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
            this.Bounciness.Location = new System.Drawing.Point(124, 63);
            this.Bounciness.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Bounciness.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Bounciness.Name = "Bounciness";
            this.Bounciness.Size = new System.Drawing.Size(84, 26);
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
            this.label6.Location = new System.Drawing.Point(22, 108);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(84, 20);
            this.label6.TabIndex = 17;
            this.label6.Text = "Air Friction";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(22, 234);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(119, 20);
            this.label7.TabIndex = 18;
            this.label7.Text = "Ground Friction";
            // 
            // AirFrictionX
            // 
            this.AirFrictionX.DecimalPlaces = 2;
            this.AirFrictionX.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.AirFrictionX.Location = new System.Drawing.Point(124, 129);
            this.AirFrictionX.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.AirFrictionX.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionX.Name = "AirFrictionX";
            this.AirFrictionX.Size = new System.Drawing.Size(84, 26);
            this.AirFrictionX.TabIndex = 19;
            this.AirFrictionX.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionX.ValueChanged += new System.EventHandler(this.AirFrictionX_ValueChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(85, 132);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(20, 20);
            this.label4.TabIndex = 20;
            this.label4.Text = "X";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(85, 172);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(20, 20);
            this.label8.TabIndex = 22;
            this.label8.Text = "Y";
            // 
            // AirFrictionY
            // 
            this.AirFrictionY.DecimalPlaces = 2;
            this.AirFrictionY.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.AirFrictionY.Location = new System.Drawing.Point(124, 169);
            this.AirFrictionY.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.AirFrictionY.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionY.Name = "AirFrictionY";
            this.AirFrictionY.Size = new System.Drawing.Size(84, 26);
            this.AirFrictionY.TabIndex = 21;
            this.AirFrictionY.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionY.ValueChanged += new System.EventHandler(this.AirFrictionY_ValueChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(85, 302);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(20, 20);
            this.label9.TabIndex = 26;
            this.label9.Text = "Y";
            // 
            // GroundFrictionY
            // 
            this.GroundFrictionY.DecimalPlaces = 2;
            this.GroundFrictionY.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.GroundFrictionY.Location = new System.Drawing.Point(124, 299);
            this.GroundFrictionY.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroundFrictionY.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionY.Name = "GroundFrictionY";
            this.GroundFrictionY.Size = new System.Drawing.Size(84, 26);
            this.GroundFrictionY.TabIndex = 25;
            this.GroundFrictionY.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionY.ValueChanged += new System.EventHandler(this.GroundFrictionY_ValueChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(85, 262);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(20, 20);
            this.label10.TabIndex = 24;
            this.label10.Text = "X";
            // 
            // GroundFrictionX
            // 
            this.GroundFrictionX.DecimalPlaces = 2;
            this.GroundFrictionX.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.GroundFrictionX.Location = new System.Drawing.Point(124, 259);
            this.GroundFrictionX.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroundFrictionX.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionX.Name = "GroundFrictionX";
            this.GroundFrictionX.Size = new System.Drawing.Size(84, 26);
            this.GroundFrictionX.TabIndex = 23;
            this.GroundFrictionX.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionX.ValueChanged += new System.EventHandler(this.GroundFrictionX_ValueChanged);
            // 
            // SaveBtn
            // 
            this.SaveBtn.Location = new System.Drawing.Point(18, 389);
            this.SaveBtn.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SaveBtn.Name = "SaveBtn";
            this.SaveBtn.Size = new System.Drawing.Size(112, 35);
            this.SaveBtn.TabIndex = 27;
            this.SaveBtn.Text = "&Save";
            this.SaveBtn.UseVisualStyleBackColor = true;
            this.SaveBtn.Click += new System.EventHandler(this.SaveBtn_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(282, 29);
            this.label11.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(26, 20);
            this.label11.TabIndex = 28;
            this.label11.Text = "ID";
            // 
            // IDText
            // 
            this.IDText.AutoSize = true;
            this.IDText.Location = new System.Drawing.Point(380, 29);
            this.IDText.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.IDText.Name = "IDText";
            this.IDText.Size = new System.Drawing.Size(18, 20);
            this.IDText.TabIndex = 29;
            this.IDText.Text = "0";
            // 
            // EnemyTagCheckbox
            // 
            this.EnemyTagCheckbox.AutoSize = true;
            this.EnemyTagCheckbox.Location = new System.Drawing.Point(24, 20);
            this.EnemyTagCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.EnemyTagCheckbox.Name = "EnemyTagCheckbox";
            this.EnemyTagCheckbox.Size = new System.Drawing.Size(84, 24);
            this.EnemyTagCheckbox.TabIndex = 30;
            this.EnemyTagCheckbox.Text = "Enemy";
            this.EnemyTagCheckbox.UseVisualStyleBackColor = true;
            this.EnemyTagCheckbox.CheckedChanged += new System.EventHandler(this.PickableTagCheckbox_CheckedChanged);
            // 
            // PickableTagCheckbox
            // 
            this.PickableTagCheckbox.AutoSize = true;
            this.PickableTagCheckbox.Location = new System.Drawing.Point(24, 126);
            this.PickableTagCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.PickableTagCheckbox.Name = "PickableTagCheckbox";
            this.PickableTagCheckbox.Size = new System.Drawing.Size(94, 24);
            this.PickableTagCheckbox.TabIndex = 33;
            this.PickableTagCheckbox.Text = "&Pickable";
            this.PickableTagCheckbox.UseVisualStyleBackColor = true;
            this.PickableTagCheckbox.CheckedChanged += new System.EventHandler(this.PickableTagCheckbox_CheckedChanged);
            // 
            // BulletTagCheckbox
            // 
            this.BulletTagCheckbox.AutoSize = true;
            this.BulletTagCheckbox.Location = new System.Drawing.Point(24, 91);
            this.BulletTagCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.BulletTagCheckbox.Name = "BulletTagCheckbox";
            this.BulletTagCheckbox.Size = new System.Drawing.Size(75, 24);
            this.BulletTagCheckbox.TabIndex = 32;
            this.BulletTagCheckbox.Text = "&Bullet";
            this.BulletTagCheckbox.UseVisualStyleBackColor = true;
            this.BulletTagCheckbox.CheckedChanged += new System.EventHandler(this.PickableTagCheckbox_CheckedChanged);
            // 
            // PlayerTagCheckbox
            // 
            this.PlayerTagCheckbox.AutoSize = true;
            this.PlayerTagCheckbox.Location = new System.Drawing.Point(24, 55);
            this.PlayerTagCheckbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.PlayerTagCheckbox.Name = "PlayerTagCheckbox";
            this.PlayerTagCheckbox.Size = new System.Drawing.Size(78, 24);
            this.PlayerTagCheckbox.TabIndex = 31;
            this.PlayerTagCheckbox.Text = "Player";
            this.PlayerTagCheckbox.UseVisualStyleBackColor = true;
            this.PlayerTagCheckbox.CheckedChanged += new System.EventHandler(this.PickableTagCheckbox_CheckedChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(286, 109);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(431, 383);
            this.tabControl1.TabIndex = 33;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.Weight);
            this.tabPage1.Controls.Add(this.Bounciness);
            this.tabPage1.Controls.Add(this.label6);
            this.tabPage1.Controls.Add(this.label7);
            this.tabPage1.Controls.Add(this.label9);
            this.tabPage1.Controls.Add(this.AirFrictionX);
            this.tabPage1.Controls.Add(this.RotationCheckbox);
            this.tabPage1.Controls.Add(this.GroundFrictionY);
            this.tabPage1.Controls.Add(this.KineticCheckbox);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Controls.Add(this.GravityCheckbox);
            this.tabPage1.Controls.Add(this.label10);
            this.tabPage1.Controls.Add(this.PhysicsCheckbox);
            this.tabPage1.Controls.Add(this.AirFrictionY);
            this.tabPage1.Controls.Add(this.GroundFrictionX);
            this.tabPage1.Controls.Add(this.label8);
            this.tabPage1.Location = new System.Drawing.Point(4, 29);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(423, 350);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Physics";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.VariableGrid);
            this.tabPage2.Controls.Add(this.DefaultValueLabel);
            this.tabPage2.Controls.Add(this.VariableDefaultValue);
            this.tabPage2.Controls.Add(this.VariableListBox);
            this.tabPage2.Controls.Add(this.RenameVaribleBtn);
            this.tabPage2.Controls.Add(this.RemoveVariableBtn);
            this.tabPage2.Controls.Add(this.AddVaribleBtn);
            this.tabPage2.Location = new System.Drawing.Point(4, 29);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(423, 350);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Variables";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // VariableGrid
            // 
            this.VariableGrid.AllowUserToAddRows = false;
            this.VariableGrid.AllowUserToDeleteRows = false;
            this.VariableGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.VariableGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.VariableName,
            this.Value});
            this.VariableGrid.Location = new System.Drawing.Point(19, 27);
            this.VariableGrid.MultiSelect = false;
            this.VariableGrid.Name = "VariableGrid";
            this.VariableGrid.RowHeadersVisible = false;
            this.VariableGrid.RowHeadersWidth = 62;
            this.VariableGrid.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.VariableGrid.RowTemplate.Height = 28;
            this.VariableGrid.Size = new System.Drawing.Size(317, 215);
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
            this.DefaultValueLabel.Location = new System.Drawing.Point(269, 27);
            this.DefaultValueLabel.Name = "DefaultValueLabel";
            this.DefaultValueLabel.Size = new System.Drawing.Size(102, 20);
            this.DefaultValueLabel.TabIndex = 5;
            this.DefaultValueLabel.Text = "Default value";
            // 
            // VariableDefaultValue
            // 
            this.VariableDefaultValue.DecimalPlaces = 2;
            this.VariableDefaultValue.Location = new System.Drawing.Point(273, 50);
            this.VariableDefaultValue.Name = "VariableDefaultValue";
            this.VariableDefaultValue.Size = new System.Drawing.Size(120, 26);
            this.VariableDefaultValue.TabIndex = 4;
            this.VariableDefaultValue.ValueChanged += new System.EventHandler(this.VariableDefaultValue_ValueChanged);
            // 
            // VariableListBox
            // 
            this.VariableListBox.FormattingEnabled = true;
            this.VariableListBox.ItemHeight = 20;
            this.VariableListBox.Location = new System.Drawing.Point(318, -20);
            this.VariableListBox.Name = "VariableListBox";
            this.VariableListBox.Size = new System.Drawing.Size(227, 144);
            this.VariableListBox.TabIndex = 3;
            this.VariableListBox.SelectedIndexChanged += new System.EventHandler(this.VariableListBox_SelectedIndexChanged);
            // 
            // RenameVaribleBtn
            // 
            this.RenameVaribleBtn.Location = new System.Drawing.Point(255, 286);
            this.RenameVaribleBtn.Name = "RenameVaribleBtn";
            this.RenameVaribleBtn.Size = new System.Drawing.Size(92, 35);
            this.RenameVaribleBtn.TabIndex = 2;
            this.RenameVaribleBtn.Text = "Rename";
            this.RenameVaribleBtn.UseVisualStyleBackColor = true;
            // 
            // RemoveVariableBtn
            // 
            this.RemoveVariableBtn.Location = new System.Drawing.Point(121, 286);
            this.RemoveVariableBtn.Name = "RemoveVariableBtn";
            this.RemoveVariableBtn.Size = new System.Drawing.Size(92, 35);
            this.RemoveVariableBtn.TabIndex = 1;
            this.RemoveVariableBtn.Text = "&Remove";
            this.RemoveVariableBtn.UseVisualStyleBackColor = true;
            this.RemoveVariableBtn.Click += new System.EventHandler(this.RemoveVariableBtn_Click);
            // 
            // AddVaribleBtn
            // 
            this.AddVaribleBtn.Location = new System.Drawing.Point(6, 286);
            this.AddVaribleBtn.Name = "AddVaribleBtn";
            this.AddVaribleBtn.Size = new System.Drawing.Size(92, 34);
            this.AddVaribleBtn.TabIndex = 0;
            this.AddVaribleBtn.Text = "&Add";
            this.AddVaribleBtn.UseVisualStyleBackColor = true;
            this.AddVaribleBtn.Click += new System.EventHandler(this.AddVaribleBtn_Click);
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.PickableTagCheckbox);
            this.tabPage3.Controls.Add(this.BulletTagCheckbox);
            this.tabPage3.Controls.Add(this.EnemyTagCheckbox);
            this.tabPage3.Controls.Add(this.PlayerTagCheckbox);
            this.tabPage3.Location = new System.Drawing.Point(4, 29);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(423, 350);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Collision tags";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // GameObjectEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(938, 511);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.IDText);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.SaveBtn);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.NameText);
            this.Controls.Add(this.SelectPicBtn);
            this.Controls.Add(this.GameObjectPic);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.RemoveBtn);
            this.Controls.Add(this.NewBtn);
            this.Controls.Add(this.GameObjectTypeList);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "GameObjectEditor";
            this.Text = "GameObjectEditor";
            this.Load += new System.EventHandler(this.GameObjectEditor_Load);
            ((System.ComponentModel.ISupportInitialize)(this.GameObjectPic)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Weight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Bounciness)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionX)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.VariableGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.VariableDefaultValue)).EndInit();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox GameObjectTypeList;
        private System.Windows.Forms.Button NewBtn;
        private System.Windows.Forms.Button RemoveBtn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox GameObjectPic;
        private System.Windows.Forms.Button SelectPicBtn;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox PhysicsCheckbox;
        private System.Windows.Forms.CheckBox GravityCheckbox;
        private System.Windows.Forms.CheckBox KineticCheckbox;
        private System.Windows.Forms.CheckBox RotationCheckbox;
        private System.Windows.Forms.TextBox NameText;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown Weight;
        private System.Windows.Forms.NumericUpDown Bounciness;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown AirFrictionX;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown AirFrictionY;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.NumericUpDown GroundFrictionY;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.NumericUpDown GroundFrictionX;
        private System.Windows.Forms.Button SaveBtn;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label IDText;
        private System.Windows.Forms.CheckBox EnemyTagCheckbox;
        private System.Windows.Forms.CheckBox PickableTagCheckbox;
        private System.Windows.Forms.CheckBox BulletTagCheckbox;
        private System.Windows.Forms.CheckBox PlayerTagCheckbox;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Label DefaultValueLabel;
        private System.Windows.Forms.NumericUpDown VariableDefaultValue;
        private System.Windows.Forms.ListBox VariableListBox;
        private System.Windows.Forms.Button RenameVaribleBtn;
        private System.Windows.Forms.Button RemoveVariableBtn;
        private System.Windows.Forms.Button AddVaribleBtn;
        private System.Windows.Forms.DataGridViewTextBoxColumn VariableName;
        private System.Windows.Forms.DataGridViewTextBoxColumn Value;
        private System.Windows.Forms.DataGridView VariableGrid;
    }
}