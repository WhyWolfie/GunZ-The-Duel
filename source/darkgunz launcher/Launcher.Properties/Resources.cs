using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.Resources;
using System.Runtime.CompilerServices;

namespace Launcher.Properties
{
	[CompilerGenerated]
	[DebuggerNonUserCode]
	[GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")]
	internal class Resources
	{
		private static ResourceManager resourceMan;

		private static CultureInfo resourceCulture;

		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static ResourceManager ResourceManager
		{
			get
			{
				if (object.ReferenceEquals(resourceMan, null))
				{
					ResourceManager resourceManager = resourceMan = new ResourceManager("Launcher.Properties.Resources", typeof(Resources).Assembly);
				}
				return resourceMan;
			}
		}

		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static CultureInfo Culture
		{
			get
			{
				return resourceCulture;
			}
			set
			{
				resourceCulture = value;
			}
		}

		internal static Bitmap carbonfiber
		{
			get
			{
				object @object = ResourceManager.GetObject("carbonfiber", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static Bitmap Closehover
		{
			get
			{
				object @object = ResourceManager.GetObject("Closehover", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static Bitmap Closenormal
		{
			get
			{
				object @object = ResourceManager.GetObject("Closenormal", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static Bitmap FULL
		{
			get
			{
				object @object = ResourceManager.GetObject("FULL", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static Bitmap launcher
		{
			get
			{
				object @object = ResourceManager.GetObject("launcher", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static Bitmap minhover
		{
			get
			{
				object @object = ResourceManager.GetObject("minhover", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static Bitmap minnormal
		{
			get
			{
				object @object = ResourceManager.GetObject("minnormal", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static Bitmap Playdisabled
		{
			get
			{
				object @object = ResourceManager.GetObject("Playdisabled", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static Bitmap Playhover
		{
			get
			{
				object @object = ResourceManager.GetObject("Playhover", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static Bitmap Playnormal
		{
			get
			{
				object @object = ResourceManager.GetObject("Playnormal", resourceCulture);
				return (Bitmap)@object;
			}
		}

		internal static byte[] SelfPatch
		{
			get
			{
				object @object = ResourceManager.GetObject("SelfPatch", resourceCulture);
				return (byte[])@object;
			}
		}

		internal Resources()
		{
		}
	}
}
