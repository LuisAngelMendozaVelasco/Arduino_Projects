namespace _01_1_Blink
{
    partial class Form1
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
            this.comboBox_Ports = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button_Connect_Disconnect = new System.Windows.Forms.Button();
            this.button_LED = new System.Windows.Forms.Button();
            this.button_Start_Stop_Blinking = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // comboBox_Ports
            // 
            this.comboBox_Ports.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_Ports.FormattingEnabled = true;
            this.comboBox_Ports.Location = new System.Drawing.Point(12, 29);
            this.comboBox_Ports.Name = "comboBox_Ports";
            this.comboBox_Ports.Size = new System.Drawing.Size(121, 21);
            this.comboBox_Ports.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "COM Ports:";
            // 
            // button_Connect_Disconnect
            // 
            this.button_Connect_Disconnect.Location = new System.Drawing.Point(12, 56);
            this.button_Connect_Disconnect.Name = "button_Connect_Disconnect";
            this.button_Connect_Disconnect.Size = new System.Drawing.Size(121, 23);
            this.button_Connect_Disconnect.TabIndex = 2;
            this.button_Connect_Disconnect.Text = "Connect";
            this.button_Connect_Disconnect.UseVisualStyleBackColor = true;
            this.button_Connect_Disconnect.Click += new System.EventHandler(this.button_Connect_Disconnect_Click);
            // 
            // button_LED
            // 
            this.button_LED.Enabled = false;
            this.button_LED.Location = new System.Drawing.Point(139, 47);
            this.button_LED.Name = "button_LED";
            this.button_LED.Size = new System.Drawing.Size(40, 40);
            this.button_LED.TabIndex = 4;
            this.button_LED.Text = "LED";
            this.button_LED.UseVisualStyleBackColor = true;
            // 
            // button_Start_Stop_Blinking
            // 
            this.button_Start_Stop_Blinking.Location = new System.Drawing.Point(12, 85);
            this.button_Start_Stop_Blinking.Name = "button_Start_Stop_Blinking";
            this.button_Start_Stop_Blinking.Size = new System.Drawing.Size(121, 23);
            this.button_Start_Stop_Blinking.TabIndex = 5;
            this.button_Start_Stop_Blinking.Text = "Start blinking";
            this.button_Start_Stop_Blinking.UseVisualStyleBackColor = true;
            this.button_Start_Stop_Blinking.Click += new System.EventHandler(this.button_Start_Stop_Blinking_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(230, 176);
            this.Controls.Add(this.button_Start_Stop_Blinking);
            this.Controls.Add(this.button_LED);
            this.Controls.Add(this.button_Connect_Disconnect);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBox_Ports);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox_Ports;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button_Connect_Disconnect;
        private System.Windows.Forms.Button button_LED;
        private System.Windows.Forms.Button button_Start_Stop_Blinking;
    }
}

