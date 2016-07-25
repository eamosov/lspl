package ru.lspl;

import java.io.File;
import java.io.IOException;

import ru.lspl.utils.NativeUtils;
import ru.lspl.utils.OsCheck;

public abstract class LsplObject {

	public final int id;

	public static native String dumpMemoryStats();

	public static native void setRml( String rml );

	private static native void initStatic();
	
	

	static {
	    try {
	        OsCheck.OSType ostype=OsCheck.getOperatingSystemType();
	        switch (ostype) {
	            case MacOS:
	                NativeUtils.loadLibraryFromJar("/lib/mac/liblspl.so");
	                NativeUtils.loadLibraryFromJar("/lib/mac/liblspl-java.so");
	                break;
	            case Linux:
                    NativeUtils.loadLibraryFromJar("/lib/linux/liblspl.so");
                    NativeUtils.loadLibraryFromJar("/lib/linux/liblspl-java.so");
                    break;	                
	            default:
	                break;
	        }

	        final File tmpDataDir = NativeUtils.copyFileToTmp(LsplObject.class.getResource("/rml"));
	        LsplObject.setRml(tmpDataDir.getAbsolutePath());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

		initStatic();
	}

	protected LsplObject( int id ) {
		this.id = id;
	}

	@Override
	public boolean equals( Object o ) {
		if ( o == this )
			return true;
		if ( o == null )
			return false;
		if ( !o.getClass().equals( getClass() ) )
			return false;

		return id == ((LsplObject) o).id;
	}

}