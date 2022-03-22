using Launcher.Properties;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace Launcher
{
	public class WolfProgressBar : Control
	{
		private const BufferedGraphics NO_MANAGED_BACK_BUFFER = null;

		private BufferedGraphicsContext GraphicManager;

		private BufferedGraphics ManagedBackBuffer;

		private int max = 100;

		private int min = 0;

		private int val = 0;

		private int height = 24;

		private int width = 500;

		private bool first = true;

		private int major = Environment.OSVersion.Version.Major;

		private int minor = Environment.OSVersion.Version.Minor;

		private bool disposing = false;

		public int Minimum
		{
			get
			{
				return min;
			}
			set
			{
				if (value < 0)
				{
					min = 0;
				}
				if (value > max)
				{
					min = value;
					min = value;
				}
				if (val < min)
				{
					val = min;
				}
				Invalidate();
			}
		}

		public int Maximum
		{
			get
			{
				return max;
			}
			set
			{
				if (value < min)
				{
					min = value;
				}
				max = value;
				if (val > max)
				{
					val = max;
				}
				Invalidate();
			}
		}

		public int Value
		{
			get
			{
				return val;
			}
			set
			{
				int num = val;
				if (value < min)
				{
					val = min;
				}
				else if (value > max)
				{
					val = max;
				}
				else
				{
					val = value;
				}
				Invalidate();
			}
		}

		public override string Text
		{
			get
			{
				return base.Text;
			}
			set
			{
				base.Text = value;
				Invalidate();
			}
		}

		private void MemoryCleanup(object sender, EventArgs e)
		{
			if (ManagedBackBuffer != null)
			{
				ManagedBackBuffer.Dispose();
			}
		}

		protected override void OnPaint(PaintEventArgs pe)
		{
			if (first)
			{
				first = false;
				try
				{
					Application.ApplicationExit += MemoryCleanup;
					SetStyle(ControlStyles.AllPaintingInWmPaint, value: true);
					SetStyle(ControlStyles.OptimizedDoubleBuffer, value: true);
					width = base.Width;
					height = base.Height;
					GraphicManager = BufferedGraphicsManager.Current;
					GraphicManager.MaximumBuffer = new Size(base.Width + 1, base.Height + 1);
					ManagedBackBuffer = GraphicManager.Allocate(CreateGraphics(), base.ClientRectangle);
				}
				catch (Exception e)
				{
					DG.Log("Wo1fProgressBar::OnPaint(1)", e);
				}
			}
			try
			{
				DrawProgressBar(ManagedBackBuffer.Graphics);
				ManagedBackBuffer.Render(pe.Graphics);
			}
			catch (Exception e)
			{
				DG.Log("WolfProgressBar::OnPaint() 2", e);
			}
		}

		private void DoubleBufferedControl_Resize(object sender, EventArgs e)
		{
			if (ManagedBackBuffer != null)
			{
				BackBufferManagedBackBufferDispose();
			}
			GraphicManager.MaximumBuffer = new Size(base.Width + 1, base.Height + 1);
			ManagedBackBuffer = GraphicManager.Allocate(CreateGraphics(), base.ClientRectangle);
			Refresh();
		}

		private void BackBufferManagedBackBufferDispose()
		{
		}

		private void DrawProgressBar(Graphics G)
		{
			try
			{
				if (base.Height != 0 && base.Width != 0)
				{
					height = base.Height;
					width = base.Width;
					if (GraphicManager.MaximumBuffer.Width != width + 1 || GraphicManager.MaximumBuffer.Height != height + 1)
					{
						GraphicManager.MaximumBuffer = new Size(base.Width + 1, base.Height + 1);
						ManagedBackBuffer = GraphicManager.Allocate(CreateGraphics(), base.ClientRectangle);
					}
				}
				Bitmap bitmap = null;
				bitmap = new Bitmap(width, height);
				float num = (float)(val - min) / (float)(max - min);
				Rectangle clientRectangle = base.ClientRectangle;
				clientRectangle.Width = (int)((float)clientRectangle.Width * num);
				Rectangle destRect = new Rectangle(0, 0, clientRectangle.Width, clientRectangle.Height);
				Rectangle srcRect = new Rectangle(new Point(0, 0), destRect.Size);
				G.DrawImage(srcRect: new Rectangle(new Point(0, 0), Resources.carbonfiber.Size), image: Resources.carbonfiber, destRect: base.ClientRectangle, srcUnit: GraphicsUnit.Pixel);
				G.FillRectangle(new SolidBrush(Color.FromArgb(230, Color.Black)), base.ClientRectangle);
				if (destRect.Width > 0)
				{
					if (major < 6)
					{
						Bitmap bitmap2 = new Bitmap(destRect.Width, destRect.Height);
						using (Graphics graphics = Graphics.FromImage(bitmap2))
						{
							graphics.DrawImage(Resources.FULL, new Rectangle(0, 0, bitmap2.Width, bitmap2.Height), srcRect, GraphicsUnit.Pixel);
						}
						G.DrawImage(bitmap2, new Point(0, 0));
					}
					else if (major == 6 && minor == 0)
					{
						Bitmap bitmap2 = new Bitmap(destRect.Width, destRect.Height);
						using (Graphics graphics = Graphics.FromImage(bitmap2))
						{
							graphics.DrawImage(Resources.FULL, new Rectangle(0, 0, bitmap2.Width, bitmap2.Height), srcRect, GraphicsUnit.Pixel);
						}
						G.DrawImage(bitmap2, new Point(0, 0));
					}
					else
					{
						G.DrawImage(Resources.FULL, destRect, srcRect, GraphicsUnit.Point);
					}
				}
				float x = 5f;
				float num2 = base.Height / 2;
				float num3 = Font.GetHeight() / 2f;
				float y = num2 - num3 - 2f;
				if (Text.Contains("\n"))
				{
					y = 0f;
				}
				G.DrawString(Text, Font, new SolidBrush(ForeColor), new RectangleF(new PointF(x, y), new SizeF(base.Size)));
			}
			catch (Exception ex)
			{
				DG.Log("Exception in progress bar - MSG: " + ex.Message + Environment.NewLine + "Trace: " + ex.StackTrace);
			}
		}

		protected override void Dispose(bool disposing)
		{
			disposing = true;
			base.Dispose(disposing);
		}

		protected override void OnResize(EventArgs e)
		{
			Invalidate();
		}
	}
}
