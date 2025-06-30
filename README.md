# USD Anywhere - System Design Documentation

Overview

USD Anywhere is a distributed content pipeline system designed to help independent filmmakers and animation teams collaborate remotely using the Universal Scene Description (OpenUSD) format. The system handles content versioning, network-free collaboration, scene referencing, and real-time asset updates.

This documentation describes the architecture, system components, workflows, and interaction models of the USD Anywhere platform.

Goals

Enable artists to collaboratively edit and share USD files.

Maintain content structure and layer hierarchy.

Provide a visual dashboard for asset browsing, update status, and download or live-link options.

Support GitHub-based workflows (including GitHub Actions).

Prepare for future integration of full web application support.

System Components

1. Blender USD Delegate (C++)

Responsible for loading, modifying, and saving USD files in Blender.

Applies overrides to prims and saves them non-destructively.

Interfaces with Blender's depsgraph for tracking user changes.

Supports usdrecord for generating quick USD-based renders.

Uses POSIX threading for concurrency control.

2. Python Node (Blender Plugin)

Integrates with the Blender UI.

Detects user modifications and communicates changes back to the C++ delegate.

Facilitates saving/loading directly from within Blender.

3. Web Application (React + FastAPI)

Visual dashboard for managing USD files.

Displays file update status (e.g., synced, modified, uploaded).

Allows loading files directly into Blender via the custom USD Node.

Interfaces with backend API for file browsing, metadata, and downloads.

4. Database (PostgreSQL or SQLite)

Stores file metadata, versioning history, and access logs.

Tracks user sessions and reference maps.

5. GitHub Runners (Optional Deployment)

Enables automated validation, formatting, and push integration.

Artists can commit scene fragments to a GitHub repository..

![ff7e890f-bdef-4672-8d92-3f1d013374d8](https://github.com/user-attachments/assets/036317d3-7309-4bc9-b225-19ba4a857520)
