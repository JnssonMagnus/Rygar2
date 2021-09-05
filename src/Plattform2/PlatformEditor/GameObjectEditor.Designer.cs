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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.PickableTagCheckbox = new System.Windows.Forms.CheckBox();
            this.BulletTagCheckbox = new System.Windows.Forms.CheckBox();
            this.PlayerTagCheckbox = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.GameObjectPic)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Weight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Bounciness)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AirFrictionY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroundFrictionX)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // GameObjectTypeList
            // 
            this.GameObjectTypeList.FormattingEnabled = true;
            this.GameObjectTypeList.Location = new System.Drawing.Point(12, 38);
            this.GameObjectTypeList.Name = "GameObjectTypeList";
            this.GameObjectTypeList.Size = new System.Drawing.Size(157, 134);
            this.GameObjectTypeList.TabIndex = 0;
            this.GameObjectTypeList.SelectedIndexChanged += new System.EventHandler(this.GameObjectTypeList_SelectedIndexChanged);
            // 
            // NewBtn
            // 
            this.NewBtn.Location = new System.Drawing.Point(12, 178);
            this.NewBtn.Name = "NewBtn";
            this.NewBtn.Size = new System.Drawing.Size(75, 23);
            this.NewBtn.TabIndex = 1;
            this.NewBtn.Text = "&New";
            this.NewBtn.UseVisualStyleBackColor = true;
            this.NewBtn.Click += new System.EventHandler(this.NewBtn_Click);
            // 
            // RemoveBtn
            // 
            this.RemoveBtn.Location = new System.Drawing.Point(94, 178);
            this.RemoveBtn.Name = "RemoveBtn";
            this.RemoveBtn.Size = new System.Drawing.Size(75, 23);
            this.RemoveBtn.TabIndex = 2;
            this.RemoveBtn.Text = "&Remove";
            this.RemoveBtn.UseVisualStyleBackColor = true;
            this.RemoveBtn.Click += new System.EventHandler(this.RemoveBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(188, 41);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Name";
            // 
            // GameObjectPic
            // 
            this.GameObjectPic.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.GameObjectPic.Location = new System.Drawing.Point(511, 148);
            this.GameObjectPic.Name = "GameObjectPic";
            this.GameObjectPic.Size = new System.Drawing.Size(100, 100);
            this.GameObjectPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.GameObjectPic.TabIndex = 4;
            this.GameObjectPic.TabStop = false;
            // 
            // SelectPicBtn
            // 
            this.SelectPicBtn.Location = new System.Drawing.Point(584, 254);
            this.SelectPicBtn.Name = "SelectPicBtn";
            this.SelectPicBtn.Size = new System.Drawing.Size(27, 23);
            this.SelectPicBtn.TabIndex = 5;
            this.SelectPicBtn.Text = "..";
            this.SelectPicBtn.UseVisualStyleBackColor = true;
            this.SelectPicBtn.Click += new System.EventHandler(this.SelectPicBtn_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(188, 97);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Bounciness";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(188, 71);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Weight";
            // 
            // PhysicsCheckbox
            // 
            this.PhysicsCheckbox.AutoSize = true;
            this.PhysicsCheckbox.Location = new System.Drawing.Point(508, 28);
            this.PhysicsCheckbox.Name = "PhysicsCheckbox";
            this.PhysicsCheckbox.Size = new System.Drawing.Size(103, 17);
            this.PhysicsCheckbox.TabIndex = 8;
            this.PhysicsCheckbox.Text = "Physics enabled";
            this.PhysicsCheckbox.UseVisualStyleBackColor = true;
            this.PhysicsCheckbox.CheckedChanged += new System.EventHandler(this.PhysicsCheckbox_CheckedChanged);
            // 
            // GravityCheckbox
            // 
            this.GravityCheckbox.AutoSize = true;
            this.GravityCheckbox.Location = new System.Drawing.Point(508, 52);
            this.GravityCheckbox.Name = "GravityCheckbox";
            this.GravityCheckbox.Size = new System.Drawing.Size(59, 17);
            this.GravityCheckbox.TabIndex = 9;
            this.GravityCheckbox.Text = "Gravity";
            this.GravityCheckbox.UseVisualStyleBackColor = true;
            this.GravityCheckbox.CheckedChanged += new System.EventHandler(this.GravityCheckbox_CheckedChanged);
            // 
            // KineticCheckbox
            // 
            this.KineticCheckbox.AutoSize = true;
            this.KineticCheckbox.Location = new System.Drawing.Point(508, 76);
            this.KineticCheckbox.Name = "KineticCheckbox";
            this.KineticCheckbox.Size = new System.Drawing.Size(58, 17);
            this.KineticCheckbox.TabIndex = 10;
            this.KineticCheckbox.Text = "Kinetic";
            this.KineticCheckbox.UseVisualStyleBackColor = true;
            this.KineticCheckbox.CheckedChanged += new System.EventHandler(this.KineticCheckbox_CheckedChanged);
            // 
            // RotationCheckbox
            // 
            this.RotationCheckbox.AutoSize = true;
            this.RotationCheckbox.Location = new System.Drawing.Point(508, 100);
            this.RotationCheckbox.Name = "RotationCheckbox";
            this.RotationCheckbox.Size = new System.Drawing.Size(91, 17);
            this.RotationCheckbox.TabIndex = 11;
            this.RotationCheckbox.Text = "Auto Rotation";
            this.RotationCheckbox.UseVisualStyleBackColor = true;
            this.RotationCheckbox.CheckedChanged += new System.EventHandler(this.RotationCheckbox_CheckedChanged);
            // 
            // NameText
            // 
            this.NameText.Location = new System.Drawing.Point(256, 38);
            this.NameText.Name = "NameText";
            this.NameText.Size = new System.Drawing.Size(114, 20);
            this.NameText.TabIndex = 12;
            this.NameText.TextChanged += new System.EventHandler(this.NameText_TextChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 19);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(101, 13);
            this.label5.TabIndex = 14;
            this.label5.Text = "Game Object Types";
            // 
            // Weight
            // 
            this.Weight.DecimalPlaces = 2;
            this.Weight.Location = new System.Drawing.Point(256, 71);
            this.Weight.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.Weight.Name = "Weight";
            this.Weight.Size = new System.Drawing.Size(56, 20);
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
            this.Bounciness.Location = new System.Drawing.Point(256, 97);
            this.Bounciness.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Bounciness.Name = "Bounciness";
            this.Bounciness.Size = new System.Drawing.Size(56, 20);
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
            this.label6.Location = new System.Drawing.Point(188, 126);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(56, 13);
            this.label6.TabIndex = 17;
            this.label6.Text = "Air Friction";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(188, 208);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(79, 13);
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
            this.AirFrictionX.Location = new System.Drawing.Point(256, 140);
            this.AirFrictionX.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionX.Name = "AirFrictionX";
            this.AirFrictionX.Size = new System.Drawing.Size(56, 20);
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
            this.label4.Location = new System.Drawing.Point(230, 142);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(14, 13);
            this.label4.TabIndex = 20;
            this.label4.Text = "X";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(230, 168);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(14, 13);
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
            this.AirFrictionY.Location = new System.Drawing.Point(256, 166);
            this.AirFrictionY.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.AirFrictionY.Name = "AirFrictionY";
            this.AirFrictionY.Size = new System.Drawing.Size(56, 20);
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
            this.label9.Location = new System.Drawing.Point(230, 252);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(14, 13);
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
            this.GroundFrictionY.Location = new System.Drawing.Point(256, 250);
            this.GroundFrictionY.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionY.Name = "GroundFrictionY";
            this.GroundFrictionY.Size = new System.Drawing.Size(56, 20);
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
            this.label10.Location = new System.Drawing.Point(230, 226);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(14, 13);
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
            this.GroundFrictionX.Location = new System.Drawing.Point(256, 224);
            this.GroundFrictionX.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GroundFrictionX.Name = "GroundFrictionX";
            this.GroundFrictionX.Size = new System.Drawing.Size(56, 20);
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
            this.SaveBtn.Location = new System.Drawing.Point(12, 253);
            this.SaveBtn.Name = "SaveBtn";
            this.SaveBtn.Size = new System.Drawing.Size(75, 23);
            this.SaveBtn.TabIndex = 27;
            this.SaveBtn.Text = "&Save";
            this.SaveBtn.UseVisualStyleBackColor = true;
            this.SaveBtn.Click += new System.EventHandler(this.SaveBtn_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(188, 19);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(18, 13);
            this.label11.TabIndex = 28;
            this.label11.Text = "ID";
            // 
            // IDText
            // 
            this.IDText.AutoSize = true;
            this.IDText.Location = new System.Drawing.Point(253, 19);
            this.IDText.Name = "IDText";
            this.IDText.Size = new System.Drawing.Size(13, 13);
            this.IDText.TabIndex = 29;
            this.IDText.Text = "0";
            // 
            // EnemyTagCheckbox
            // 
            this.EnemyTagCheckbox.AutoSize = true;
            this.EnemyTagCheckbox.Location = new System.Drawing.Point(6, 22);
            this.EnemyTagCheckbox.Name = "EnemyTagCheckbox";
            this.EnemyTagCheckbox.Size = new System.Drawing.Size(58, 17);
            this.EnemyTagCheckbox.TabIndex = 30;
            this.EnemyTagCheckbox.Text = "Enemy";
            this.EnemyTagCheckbox.UseVisualStyleBackColor = true;
            this.EnemyTagCheckbox.CheckedChanged += new System.EventHandler(this.PickableTagCheckbox_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.PickableTagCheckbox);
            this.groupBox1.Controls.Add(this.BulletTagCheckbox);
            this.groupBox1.Controls.Add(this.PlayerTagCheckbox);
            this.groupBox1.Controls.Add(this.EnemyTagCheckbox);
            this.groupBox1.Location = new System.Drawing.Point(395, 19);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(95, 120);
            this.groupBox1.TabIndex = 31;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "CollisionTags";
            // 
            // PickableTagCheckbox
            // 
            this.PickableTagCheckbox.AutoSize = true;
            this.PickableTagCheckbox.Location = new System.Drawing.Point(6, 91);
            this.PickableTagCheckbox.Name = "PickableTagCheckbox";
            this.PickableTagCheckbox.Size = new System.Drawing.Size(67, 17);
            this.PickableTagCheckbox.TabIndex = 33;
            this.PickableTagCheckbox.Text = "&Pickable";
            this.PickableTagCheckbox.UseVisualStyleBackColor = true;
            this.PickableTagCheckbox.CheckedChanged += new System.EventHandler(this.PickableTagCheckbox_CheckedChanged);
            // 
            // BulletTagCheckbox
            // 
            this.BulletTagCheckbox.AutoSize = true;
            this.BulletTagCheckbox.Location = new System.Drawing.Point(6, 68);
            this.BulletTagCheckbox.Name = "BulletTagCheckbox";
            this.BulletTagCheckbox.Size = new System.Drawing.Size(52, 17);
            this.BulletTagCheckbox.TabIndex = 32;
            this.BulletTagCheckbox.Text = "&Bullet";
            this.BulletTagCheckbox.UseVisualStyleBackColor = true;
            this.BulletTagCheckbox.CheckedChanged += new System.EventHandler(this.PickableTagCheckbox_CheckedChanged);
            // 
            // PlayerTagCheckbox
            // 
            this.PlayerTagCheckbox.AutoSize = true;
            this.PlayerTagCheckbox.Location = new System.Drawing.Point(6, 45);
            this.PlayerTagCheckbox.Name = "PlayerTagCheckbox";
            this.PlayerTagCheckbox.Size = new System.Drawing.Size(55, 17);
            this.PlayerTagCheckbox.TabIndex = 31;
            this.PlayerTagCheckbox.Text = "Player";
            this.PlayerTagCheckbox.UseVisualStyleBackColor = true;
            this.PlayerTagCheckbox.CheckedChanged += new System.EventHandler(this.PickableTagCheckbox_CheckedChanged);
            // 
            // GameObjectEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(627, 287);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.IDText);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.SaveBtn);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.GroundFrictionY);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.GroundFrictionX);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.AirFrictionY);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.AirFrictionX);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.Bounciness);
            this.Controls.Add(this.Weight);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.NameText);
            this.Controls.Add(this.RotationCheckbox);
            this.Controls.Add(this.KineticCheckbox);
            this.Controls.Add(this.GravityCheckbox);
            this.Controls.Add(this.PhysicsCheckbox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.SelectPicBtn);
            this.Controls.Add(this.GameObjectPic);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.RemoveBtn);
            this.Controls.Add(this.NewBtn);
            this.Controls.Add(this.GameObjectTypeList);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
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
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
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
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox PickableTagCheckbox;
        private System.Windows.Forms.CheckBox BulletTagCheckbox;
        private System.Windows.Forms.CheckBox PlayerTagCheckbox;
    }
}