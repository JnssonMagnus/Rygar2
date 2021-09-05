namespace PlatformEditor
{
    partial class MapSettings
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
            this.MapSizeGroupBox = new System.Windows.Forms.GroupBox();
            this.HeightNumeric = new System.Windows.Forms.NumericUpDown();
            this.WidthNumeric = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.WidthLabel = new System.Windows.Forms.Label();
            this.OkBtn = new System.Windows.Forms.Button();
            this.CancelBtn = new System.Windows.Forms.Button();
            this.MapSizeGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.HeightNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.WidthNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // MapSizeGroupBox
            // 
            this.MapSizeGroupBox.Controls.Add(this.HeightNumeric);
            this.MapSizeGroupBox.Controls.Add(this.WidthNumeric);
            this.MapSizeGroupBox.Controls.Add(this.label1);
            this.MapSizeGroupBox.Controls.Add(this.WidthLabel);
            this.MapSizeGroupBox.Location = new System.Drawing.Point(12, 12);
            this.MapSizeGroupBox.Name = "MapSizeGroupBox";
            this.MapSizeGroupBox.Size = new System.Drawing.Size(185, 79);
            this.MapSizeGroupBox.TabIndex = 0;
            this.MapSizeGroupBox.TabStop = false;
            this.MapSizeGroupBox.Text = "Map Size";
            // 
            // HeightNumeric
            // 
            this.HeightNumeric.Location = new System.Drawing.Point(48, 48);
            this.HeightNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.HeightNumeric.Minimum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.HeightNumeric.Name = "HeightNumeric";
            this.HeightNumeric.Size = new System.Drawing.Size(58, 20);
            this.HeightNumeric.TabIndex = 3;
            this.HeightNumeric.Value = new decimal(new int[] {
            16,
            0,
            0,
            0});
            // 
            // WidthNumeric
            // 
            this.WidthNumeric.Location = new System.Drawing.Point(48, 20);
            this.WidthNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.WidthNumeric.Minimum = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.WidthNumeric.Name = "WidthNumeric";
            this.WidthNumeric.Size = new System.Drawing.Size(58, 20);
            this.WidthNumeric.TabIndex = 2;
            this.WidthNumeric.Value = new decimal(new int[] {
            16,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Height";
            // 
            // WidthLabel
            // 
            this.WidthLabel.AutoSize = true;
            this.WidthLabel.Location = new System.Drawing.Point(7, 20);
            this.WidthLabel.Name = "WidthLabel";
            this.WidthLabel.Size = new System.Drawing.Size(35, 13);
            this.WidthLabel.TabIndex = 0;
            this.WidthLabel.Text = "Width";
            // 
            // OkBtn
            // 
            this.OkBtn.Location = new System.Drawing.Point(13, 97);
            this.OkBtn.Name = "OkBtn";
            this.OkBtn.Size = new System.Drawing.Size(89, 23);
            this.OkBtn.TabIndex = 1;
            this.OkBtn.Text = "&Ok";
            this.OkBtn.UseVisualStyleBackColor = true;
            this.OkBtn.Click += new System.EventHandler(this.button1_Click);
            // 
            // CancelBtn
            // 
            this.CancelBtn.Location = new System.Drawing.Point(108, 97);
            this.CancelBtn.Name = "CancelBtn";
            this.CancelBtn.Size = new System.Drawing.Size(89, 23);
            this.CancelBtn.TabIndex = 2;
            this.CancelBtn.Text = "&Cancel";
            this.CancelBtn.UseVisualStyleBackColor = true;
            this.CancelBtn.Click += new System.EventHandler(this.CancelBtn_Click);
            // 
            // MapSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(208, 131);
            this.Controls.Add(this.CancelBtn);
            this.Controls.Add(this.OkBtn);
            this.Controls.Add(this.MapSizeGroupBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MapSettings";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "MapSettings";
            this.Load += new System.EventHandler(this.MapSettings_Load);
            this.MapSizeGroupBox.ResumeLayout(false);
            this.MapSizeGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.HeightNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.WidthNumeric)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox MapSizeGroupBox;
        private System.Windows.Forms.NumericUpDown WidthNumeric;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label WidthLabel;
        private System.Windows.Forms.NumericUpDown HeightNumeric;
        private System.Windows.Forms.Button OkBtn;
        private System.Windows.Forms.Button CancelBtn;
    }
}