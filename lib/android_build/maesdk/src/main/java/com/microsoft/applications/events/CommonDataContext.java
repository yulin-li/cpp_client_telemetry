package com.microsoft.applications.events;

import java.util.Vector;

/**
 * `CommonDataContexts` provide a convinient struct to convey common information to
 * detect in the data being uploaded. This is expected to be internal information that
 * the host application may have access to, but do not wish to be uploaded via the 1DS
 * SDK path.
 */
public class CommonDataContext {
    /**
     * Default constructor to initialize all properties to default values.
     */
    public CommonDataContext()
    {
        domainName = "";
        machineName = "";
        userName = "";
        userAlias = "";
        ipAddresses = new Vector<String>();
        languageIdentifiers = new Vector<String>();
        machineIds = new Vector<String>();
        outOfScopeIdentifiers = new Vector<String>();
    }

    /**
    * Domain Name for the current machine
    */
    public String domainName;

    /**
    * Friendly Machine Name
    */
    public String machineName;

    /**
    * Unique UserName such as the log-in name
    */
    public String userName;

    /**
    * Unique User Alias, if different than UserName
    */
    public String userAlias;

    /**
    * IP Addresses for local network ports such as IPv4, IPv6, etc.
    */
    public Vector<String> ipAddresses;

    /**
    * Collection of Language identifiers
    */
    public Vector<String> languageIdentifiers;

    /**
    * Collection of Machine ID such as Machine Name, Motherboard ID, MAC Address, etc.
    */
    public Vector<String> machineIds;

    /**
    * Collection of OutOfScope Identifiers such as SQM_ID, Client_ID, etc.
    */
    public Vector<String> outOfScopeIdentifiers;
}
